import os
import tempfile
import pandas as pd
import torch
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

def read_files(llm_prompt, suffix, files):
    with tempfile.TemporaryDirectory() as temp_dir:
        at_llama32 = "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"
        login(at_llama32)

        model_id = "meta-llama/Llama-3.2-3B-Instruct"
        task= "text-generation"

        tokenizer = AutoTokenizer.from_pretrained(model_id)

        model = AutoModelForCausalLM.from_pretrained(
            model_id,
            low_cpu_mem_usage=True,
            device_map='auto',
            torch_dtype=torch.float16
        )

        tl_pipeline = pipeline(
                task, 
                model=model, 
                tokenizer=tokenizer, 
                max_new_tokens=500, 
                batch_size=1
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
            prompt = get_model_prompt(row["content"], llm_prompt)
            chain = prompt | tl_model | StrOutputParser()
            output_file = os.path.join("outputs", (row["filename"].split("."))[0]+str(suffix))
            with(open(output_file, "w")) as output_file:
                output_file.write(chain.invoke({"content": row['content']}))
            output_file.close()
    pass

files = get_file_names(os.path.expanduser("~/f24-michelin/docs/COBOL/medium"))

sum_prompt = "I want you to write me a 10 senetence or less summary of this COBOL code. Respond with the filename, summary, and nothing else. If no filename is found, say so"
sum_suffix = "_summary.txt"
read_files(sum_prompt, sum_suffix, files)

section_prompt = "I want you to write a summary of each section of this COBOL code. Respond with the filename, section name, summary, and nothing else. If no filename is found, say so"
section_suffix = "_sections.txt"
read_files(section_prompt, section_suffix, files)
