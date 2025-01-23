import os
import json
import subprocess
from typing import List

dir_path = os.path.expanduser("~/f24-michelin/docs/COBOL/medium")

for filename in os.listdir(dir_path):
    file_path = os.path.join(dir_path, filename)
    with open(file_path, "r") as file:
        content = file.read()
        file.close()
    prompt = f"Generate a list of each variables referenced in the following COBOL file. Use this format for your response: (Variable name) | (One sentence summary of variable's use), Here is the file:\n {content}"
    prompt = f"I am going to give you a COBOL file, it's context starts after the character '*'. I want you to look at each section and describe it's functionality to me. If there are any variables tell me how they are manipulated. At the end tell me what you think the purpose of the file is in no more than 10 sentences.\n*\n{content}"

    try:
        result = subprocess.run(
            ["ollama", "run", "llama3.2:1b"],
            input=prompt,
            capture_output=True,
            text=True,
            check=True
        )
        append_name = filename.split(".")
        output_file = open(str(append_name[0])+"_variables.txt", "a")
        output_file.write(result.stdout)
        output_file.close()
    except subprocess.CalledProcessError as e:
        print(f"Error: {e.stderr}")
