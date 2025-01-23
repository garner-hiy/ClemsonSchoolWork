import os
import pandas as pd
import torch
import gc
import warnings
from torch.utils.data import Dataset
from torch.utils.data import DataLoader
from typing import List, Callable, Optional
from typing import List
from langchain_huggingface.llms import HuggingFacePipeline
from huggingface_hub import login
from transformers import AutoTokenizer, AutoModelForCausalLM, pipeline
from langchain_core.prompts import PromptTemplate
from langchain_core.output_parsers import StrOutputParser

# Custom Output parser 
# Takes away header information and context string out of the response
class StrOutputParser:
    def __call__(self, response: str) -> str:
        # Find the start and end of the assistant's output
        start_idx = response.find("<|start_header_id|>assistant<|end_header_file|>")
        if start_idx == -1:
            return ""
        start_idx += len("<|start_header_id|>assistant<|end_header_file|>")

        end_idx = len(response)
        
        # Extract the assistant's output
        output = response[start_idx:end_idx].strip()

        return output
    
# Define a Dataset of COBOL files
class COBOLFileDataset(Dataset):
    # Dataset has its directory string and has an optional transform and preprocess function
    # These functions can be defined at the time of creation for convenience if one operation is going to be performed
    # but in this instance they are not used
    def __init__(
            self,
            file_directory: str,
            transform: Optional[Callable] = None,
            preprocessing_fn: Optional[Callable] = None
    ):
        # Find the file paths of all .txt files 
        self.file_paths = [
            os.path.join(file_directory, f)
            for f in os.listdir(file_directory)
            if f.endswith('.txt')
        ]

        # Define the transform and preprocessing functions to whatever was passed to the assembler
        self.transform = transform
        self.preprocessing_fn = preprocessing_fn
    
    def __len__(self):
        return len(self.file_paths)
    
    # Allows users to call getitem on the dataset to return the content as a string and the name of the file
    def __getitem__(self, idx):
        file_path = self.file_paths[idx]
        filename = os.path.basename(file_path)

        with open(file_path, "r") as f:
            content = f.read()
        
        if self.preprocessing_fn:
            content=self.preprocessing_fn(content)
        
        if self.transform:
            content=self.transform(content)

        return filename, content

# Converts the user and system prompts to the prompt expected by LLaMa according to Meta
def get_model_prompt(user_prompt, system_prompt):
    template = """
        <|begin_of_text|>
        <|start_header_id|>system<|end_header_id|>
        {system_prompt}
        <|eot_id|>
        <|start_header_id|>user<|end_header_id|>
        {user_prompt}
        <|eot_id|>
        <|start_header_id|>assistant<|end_header_file|>
        """

    prompt = PromptTemplate.from_template(template.format(
        system_prompt=system_prompt,
        user_prompt=user_prompt
    ))

    return prompt

# This function returns an array of paths to all files in a passed directory
def get_file_names(dir_path):
    file_paths = []
    for filename in os.listdir(dir_path):
            file_path = os.path.join(dir_path, filename)
            file_paths.append({"path": file_path, "name":filename})
    return file_paths

# This function takes the system and user prompts, the suffix to be appended to the summary files, and the 
# DataLoader of files to read
def read_files(system_prompt, user_prompt, suffix, DataLoader):
    # It connects to the LLaMa model with Jacob's authorization token
    at_llama32 = "<insert new team huggingface token>"
    login(at_llama32)

    model_id = "meta-llama/Llama-3.1-8B-Instruct"
    task= "text-generation"

    tokenizer = AutoTokenizer.from_pretrained(model_id)

    model = AutoModelForCausalLM.from_pretrained(
        model_id,
        device_map='auto',
        torch_dtype=torch.float16
    )

    # Create a model pipeline with a token limit to improve performanve
    # Increasing the number of tokens will increase hardware use and output quality
    tl_pipeline = pipeline(
        task, 
        model=model, 
        tokenizer=tokenizer, 
        max_new_tokens=500
    )
    tl_pipeline.model.config.pad_token_id = tl_pipeline.model.config.eos_token_id

    tl_model = HuggingFacePipeline(
            pipeline = tl_pipeline
    )
    
    # Break the dataloader into batches to improve performance
    for batch in DataLoader:
        # Get the name of each file and it's content
        filenames, contents = batch
        filename = filenames[0]
        content = contents[0]
        # Convert the prompt into the format expected by LLaMa
        prompt = get_model_prompt(user_prompt + content, system_prompt)
        chain = prompt | tl_model | StrOutputParser()
        # Create the summary file and write the output to it
        output_file = os.path.join("awsoutput", (filename.split("."))[0]+str(suffix))
        with(open(output_file, "w")) as output_file:
            output_file.write(chain.invoke({"content": filename}))
        output_file.close()
        # Empty the torch cache to improve performancve
        if torch.cuda.is_available():
            torch.cuda.empty_cache()
        gc.collect()
# Ignore the setting token id message, this will for output every file otherwise
warnings.filterwarnings("ignore", message="Setting `pad_token_id`")

# Create a torch dataset at the specifed directoy
dataset = COBOLFileDataset(
    file_directory=os.path.expanduser("~/f24-michelin/docs/COBOL/medium")
)
DataLoader = DataLoader(dataset, batch_size=1, shuffle=False)

# Define system and user prompts for both prompts and invoke read_files to generate summary files
sum_system_prompt = "Your job is to analyze and summarize COBOL files. You receive instructions on what to do with the code, respond only with your answer to these instructions" 
sum_user_prompt = "Read this COBOL file and give me a 10 sentence summary of the file. Explain what you think the file is meant to do and any other files it references. Respond in english, do not write any COBOL"
sum_suffix = "_summary.txt"
read_files(sum_system_prompt, sum_user_prompt, sum_suffix, dataset, DataLoader)

section_system_prompt = "Your job is to analyze and summarize COBOL files. You receive instructions on what to do with the code, respond only with your answer to these instructions" 
section_user_prompt = "Read this COBOL file and break it into sections, write what each section is and what it accomplishes. Respond in english, do not write any COBOL"
section_suffix = "_sections.txt"
read_files(section_system_prompt, section_user_prompt, section_suffix, dataset, DataLoader)
