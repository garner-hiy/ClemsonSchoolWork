import os
import glob
import pandas as pd
import torch
import gc
from typing import List
from langchain_huggingface.llms import HuggingFacePipeline
from huggingface_hub import login
from transformers import AutoTokenizer, AutoModelForCausalLM, pipeline
from langchain_core.prompts import PromptTemplate
from langchain_core.output_parsers import StrOutputParser

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

def get_file_names(dir_path):
    file_paths = []
    for filename in os.listdir(dir_path):
            if filename.endswith(".txt"):
                file_path = os.path.join(dir_path, filename)
                file_paths.append({"path": file_path, "name":filename})
    return file_paths

def read_files(system_prompt, user_prompt, suffix, files):
    at_llama32 = "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"
    login(at_llama32)

    model_id = "meta-llama/Llama-3.1-8B-Instruct"
    task= "text-generation"

    tokenizer = AutoTokenizer.from_pretrained(model_id)

    model = AutoModelForCausalLM.from_pretrained(
        model_id,
        device_map='auto',
        torch_dtype=torch.float16
    )

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
    df = pd.DataFrame()
    
    for file_info in files:
        with open(file_info['path'], "r") as file:
            new_row = pd.DataFrame({
                "filename": [file_info['name']],
                "content": [file.read()]
            })
            df = pd.concat([df, new_row], ignore_index=True)

    for _, row in df.iterrows():
        prompt = get_model_prompt(user_prompt + row["content"], system_prompt)
        chain = prompt | tl_model | StrOutputParser()
        output_file = os.path.join("outputs", (row["filename"].split("."))[0]+str(suffix))
        with(open(output_file, "w")) as output_file:
            output_file.write(chain.invoke({"content": row['content']}))
        output_file.close()
        if torch.cuda.is_available():
            torch.cuda.empty_cache()
        gc.collect()

files = get_file_names(os.path.expanduser("~/f24-michelin/docs/COBOL/medium"))

sum_system_prompt = "Your job is to analyze and summarize COBOL files. You receive instructions on what to do with the code, respond only with your answer to these instructions" 
sum_user_prompt = "Read this COBOL file and give me a 10 sentence summary of the file. Explain what you think the file is meant to do and any other files it references. Respond in english, do not write any COBOL"
sum_suffix = "_summary.txt"
read_files(sum_system_prompt, sum_user_prompt, sum_suffix, files)

section_system_prompt = "Your job is to analyze and summarize COBOL files. You receive instructions on what to do with the code, respond only with your answer to these instructions" 
section_user_prompt = "Read this COBOL file and break it into sections, write what each section is and what it accomplishes. Respond in english, do not write any COBOL"
section_suffix = "_sections.txt"
read_files(section_system_prompt, section_user_prompt, section_suffix, files)
