#!/usr/bin/env python

################################################################################
# MICHELIN CAPSTONE RAG PIPELINE RESEARCH PROTOTYPE SOURCE F24

# README: This is the source file for the prototype RAG pipeline.
#     The final project report describes each part of this system in detail.
#     An important first step for future teams will be to develop a firm
#     understanding of the connection between the system described in the
#     report and the source code presented here. Understanding this relationship
#     will be crucial for extending this system and refining its function.
#     Despite external pressures, I want to stress again that I believe the
#     best path forward for this project is a development-heavy semester
#     focused on implementing the suggestions outlined in the project report.
#     Research should be kept at a reasonable level and should be justified by
#     tangible development followup.
#
# Best of luck!     -- J.C.
################################################################################

__import__('pysqlite3')
import sys
import glob
import os
import builtins
import logging

# this workaround fixes the issue with our Python compile
# not including sqlite because Palmetto doesn't have the lib
sys.modules['sqlite3'] = sys.modules.pop('pysqlite3')

# LangChain imports for Chroma and the pipeline itself
from langchain import hub
from langchain_community.vectorstores import Chroma
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain_huggingface import HuggingFaceEmbeddings
from langchain_core.runnables import RunnablePassthrough
from langchain_core.runnables import RunnableMap
from langchain_core.runnables import RunnableLambda
from langchain.schema import Document
from langchain_core.prompts import PromptTemplate

# imports for local huggingface pipelines
from langchain_huggingface.llms import HuggingFacePipeline
from huggingface_hub import login
from transformers import AutoTokenizer, AutoModelForCausalLM, pipeline

# imports for running the demo output carousel
from rich.console import Console
from rich.syntax import Syntax
from time import sleep

## THESE SHOULD BE COMMENTED OUT DURING DEVELOPMENT !! USEFUL WARNINGS !!       <----------------------
## (enabling these suppresses warnings that arent really important)
logging.getLogger("transformers").setLevel(logging.ERROR)
logging.getLogger("langchain").setLevel(logging.ERROR)

# String parsing function that goes at the end of the LCEL expression.
# Cleans the full model output so only the generated response is shown.
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

# String parsing function that goes at the end of the LCEL expression.
# Cleans the full model output so only the generated response is shown.
# Handles a second case where model output is slightly different.
class StrOutputParser2:
    def __call__(self, response: str) -> str:
        # Find the start and end of the assistant's output
        start_idx = response.find("<|eot_id|><|start_header_id|>assistant<|end_header_id|>")
        if start_idx == -1:
            return ""
        start_idx += len("<|eot_id|><|start_header_id|>assistant<|end_header_id|>")

        end_idx = len(response)
        
        # Extract the assistant's output
        output = response[start_idx:end_idx].strip()

        return output

#https://stackoverflow.com/questions/78429932/langchain-ollama-and-llama-3-prompt-and-response
#https://www.llama.com/docs/model-cards-and-prompt-formats/llama3_1/
def get_model_prompt(user_prompt, system_prompt, template):
    prompt = PromptTemplate.from_template(template.format(
        system_prompt=system_prompt,
        user_prompt=user_prompt
    ))

    return prompt

# TRANSLATOR STEP 1
# Turn the user question into a directive with the same or similar meaning.
def get_directive(question, template, model):

    # Create an LCEL chain from the prompt and the model
    # The prompt template is populated and passed as input to the model
    sys_prompt = """You are an assistant that translates questions into English directives. Only respond with the directive."""
    user_prompt = """What directive is most similar to this question?: {question}"""

    prompt = get_model_prompt(user_prompt, sys_prompt, template)
    chain = prompt | model | StrOutputParser()

    raw_output = chain.invoke({"question": question})
    return raw_output            

# TRANSLATOR STEP 2
# Generate an example hypothetical code snippet that shows how the directive *might* be done in code.
# We use this result with the retriever to get the actual code that does the thing estimated by the example.
def get_snippets(directive, template, model):

    # Create an LCEL chain from the prompt and the model
    # The prompt template is populated and passed as input to the model
    sys_prompt = """You are an assistant that generates C code snippets from directions. Be sure to include specific numbers and names in the code."""
    user_prompt = """Write only one code snippets for this task: {directive}. This response contains C code and nothing else."""

    prompt = get_model_prompt(user_prompt, sys_prompt, template)
    chain = prompt | model | StrOutputParser()

    raw_output = chain.invoke({"directive": directive})
    return raw_output            

# This function loads all the context files and returns a ChromaDB database
# containing those files ready for retrieval queries.
def get_retriever(file_path="./files"):
    # Mostly code I stole from Carson to load multiple files into the vector store
    # (we then get a retriever from the vector store and use that in the pipeline)
    txt_files = glob.glob(os.path.expanduser(file_path+"/*.txt"))

    # Load the context from the file path
    docs = []
    for txt_file in txt_files:
        with open(txt_file, 'r', encoding='utf-8') as file:
            content = file.read()
            docs.append(Document(page_content=content))

    # Create text splits from loaded context
    text_splitter = RecursiveCharacterTextSplitter(chunk_size=1000, chunk_overlap=200)
    splits = text_splitter.split_documents(docs)

    # Create a ChromaDB for holding the splits
    try:
        vectorstore = Chroma.from_documents(documents=splits, embedding=HuggingFaceEmbeddings(model_name="sentence-transformers/all-mpnet-base-v2"))
    except:
        print(" *** YOU NEED TO SUPPLY CONTEXT FILES FOR THE MODEL TO READ FROM *** ")
        exit(0)

    # Get number of available documents
    available_docs = len(vectorstore)

    # Adjust n_results dynamically
    n_results = min(4, available_docs)  # Request up to 4 but limit to what's available

    return vectorstore.as_retriever(search_kwargs={"k": n_results})

# Mostly for the demo we ran at the event
# Use Rich to print the retrieved splits and
# the LLM responses with nice syntax highlighting
def pretty_print(output):
    console = Console()

    syntax = Syntax(output, "c", theme="",  indent_guides=True)   

    console.print(output+"\n", width=80)

# Helper function for printing the retrieved
# context splits and giving them pretty highlighting
def print_docs(docs):
    for i, doc in enumerate(docs, 1):
        pretty_print(f"Document {i}:")


        pretty_print(doc.page_content)

        print("-" * 50)

# Shorthand for the two-step process of converting the user queries
# into pseudocode snippets for retrieval.
def translate_query(question: str, template: str, tl_model):
    result_directive = get_directive(question, template, tl_model)
    result_snippet = (get_snippets(result_directive, template, tl_model))
    return result_snippet

# Wrapper function that prints its argument and then returns it
# I found this helpful for testing the different parts of the pipeline.
def debug(value, label: str):
    pretty_print(label.upper()+" OUTPUT")
    pretty_print(value)
    return value

def main():
    
    # Not great practice but works for pretty demo output
    print = pretty_print

    # Access token for using the Llama3 models on HF.
    at_llama32 = "<new team Hugging Face access token for Llama here>"
    # Login with the access token.
    login(at_llama32)

    # Load the context documents into a vector store
    docs_retriever = get_retriever()

    # This is the prompt that tells the AI model its a RAG assistant.
    prompt = hub.pull("rlm/rag-prompt-llama3")
        

    # *** MODEL SETUP ***
    # Create the Llama3.1 model
    model_id="meta-llama/Llama-3.1-8B-Instruct"
    task="text-generation"

    # https://python.langchain.com/docs/concepts/tokens/#how-tokens-work-in-language-models
    tokenizer = AutoTokenizer.from_pretrained(model_id)

    # This is a specific way of loading a model that we need for things to work.
    # https://medium.com/@tom_21755/understanding-causal-llms-masked-llm-s-and-seq2seq-a-guide-to-language-model-training-d4457bbd07fa
    # https://huggingface.co/docs/transformers/v4.46.0/en/model_doc/auto#transformers.AutoModelForCausalLM
    model = AutoModelForCausalLM.from_pretrained(model_id, low_cpu_mem_usage=True)

    # Create a Hugging Face model pipeline where we set the parameters we want
    # (this can be done during the HuggingFacePipeline LangChain API call,
    # but it's simpler done here)
    tl_pipeline = pipeline(
            task,
            model=model, 
            tokenizer=tokenizer, 
            max_new_tokens=1000, 
            device=0,
            repetition_penalty=1.2, # Stop model from waffling
                                    # This tends to happen when
                                    # it doesn't know the answer

            temperature=0.1,        # Control model "creativity"
    )
    tl_pipeline.model.config.pad_token_id = tl_pipeline.model.config.eos_token_id

    # Convert to LangChain's llm abstraction
    tl_model = HuggingFacePipeline(
            pipeline = tl_pipeline
    )

    
    # Prompt template for Llama model
    # Various functions take this prompt as an argument.
    # Different parts are gradually filled in with specific information
    # Eventually, it's just a normal prompt string like a message you
    # might send to something like ChatGPT.

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

    # Counter for running end of semester demo
    democounter = 0

    while(True):
        
        # Uncomment this line to allow user input
        #       user_question = input("Enter some input: ")
        user_question = ""

        # Loop through three example questions for the demo
        if democounter == 0:
            user_question = "What sorting algorithm does this code use?"
            builtins.print("Enter some input: ", end="")
            print("What sorting algorithm does this code use?")
            democounter = (democounter + 1) % 3
        elif democounter == 1:
            user_question = "What does this code do?"
            builtins.print("Enter some input: ", end="")
            print("What does this code do?")
            democounter = (democounter + 1) % 3
        elif democounter == 2:
            user_question = "What does checkDuplicate do?"
            builtins.print("Enter some input: ", end="")
            print("What does checkDuplicate do?")
            democounter = (democounter + 1) % 3
        else:
            print("BAD COUNTER")
            exit(1)

        # RunnableMap for query translation and invoke retriever to get context from translated query.
        # This part is separate from the rest of the chain so we can print it.
        ret_map = RunnableMap({
            "context": RunnablePassthrough() | RunnableLambda(lambda x: docs_retriever.invoke((debug(get_snippets(debug(x, "snippet (input)"), template, tl_model), "translation")))),
            "question": RunnablePassthrough()
        })

        # Invoke query translation and retrieval
        chain_input = ret_map.invoke(user_question)

        # Print the context in the dict returned by ret_map
        print_docs(chain_input["context"])

        # Print the question
        pretty_print("Original query: " + chain_input["question"])

        # LCEL (LangChain Expression Language; learning this is IMPORTANT) for the RAG pipeline
        rag_chain = (
            RunnableMap({"context": RunnablePassthrough(), "question": RunnablePassthrough()}) # Pass the above context and question.
            | prompt                # Populate the RAG prompt template with the context and question (see above)
            | tl_model              # Pass the prompt the generator model
            | StrOutputParser2()    # Clean the output string so we only see the response
        )

        # Invoke the RAG chain by passing the context snippets (parts of source code) and the original question
        llm_output = rag_chain.invoke({"context": chain_input["context"], "question": chain_input["question"]})

        # Print the output with syntax highlighting
        pretty_print(llm_output)

        # Pause the output so people can read it during the demo
        sleep(7)

        print("\n")
if __name__ == "__main__":
    main()
