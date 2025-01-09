import os
import tempfile
import pandas as pd
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

with tempfile.TemporaryDirectory() as temp_dir:
    #Jacob's plaintext access token (Don't read if you're not Jacob)
    at_llama32 = "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"
    login(at_llama32)

    model_id = "meta-llama/Llama-3.2-3B-Instruct"
    task= "text-generation"

    tokenizer = AutoTokenizer.from_pretrained(model_id)

    model = AutoModelForCausalLM.from_pretrained(model_id)

    tl_pipeline = pipeline(
            task, model=model, tokenizer=tokenizer, max_new_tokens=1000, device=0
    )
    tl_pipeline.model.config.pad_token_id = tl_pipeline.model.config.eos_token_id

    tl_model = HuggingFacePipeline(
            pipeline = tl_pipeline
    )


    dir_path = os.path.expanduser("~/f24-michelin/docs/COBOL/medium")
    df = pd.DataFrame()
    for filename in os.listdir(dir_path):
        if filename.endswith(".txt"):
            file_path = os.path.join(dir_path, filename)
            with open(file_path, "r") as file:
                new_row = pd.DataFrame({
                    "filename": [filename],
                    "content": [file.read()]
                })
                df = pd.concat([df, new_row], ignore_index=True)

    for _, row in df.iterrows():
        prompt = get_model_prompt(row["content"],   
            "I want you to list each section of this COBOL code and describe it's functionality to me. At the end tell me what you think the purpose of the file is in no more than 10 sentences. Respond with the section name, description, and file description and nothing else")
        chain = prompt | tl_model | StrOutputParser()
        append_name = filename.split(".")
        output_file = open(row["filename"]+"_variables.txt", "w")
        output_file.write(chain.invoke({"content": row['content']}))
        output_file.close()
pass
