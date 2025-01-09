__import__('pysqlite3')
import glob
import sys
import os
sys.modules['sqlite3'] = sys.modules.pop('pysqlite3')

from langchain import hub
from langchain_core.prompts import ChatPromptTemplate
from langchain_community.vectorstores import Chroma
from langchain.text_splitter import RecursiveCharacterTextSplitter
from langchain_huggingface import HuggingFaceEmbeddings
from langchain_ollama.llms import OllamaLLM
from langchain_community.document_loaders import PyPDFLoader
from langchain_core.runnables import RunnablePassthrough
from langchain_core.output_parsers import StrOutputParser
from langchain.schema import Document

import warnings

warnings.filterwarnings("ignore", category=ResourceWarning)

def format_docs(docs):
    return "\n\n".join(doc.page_content for doc in docs)

txt_files = glob.glob(os.path.expanduser("~/f24-michelin/docs/COBOL/medium/*.txt"))

docs = []
for txt_file in txt_files:
    with open(txt_file, 'r', encoding='utf-8') as file:
        content = file.read()
        docs.append(Document(page_content=content))

text_splitter = RecursiveCharacterTextSplitter(chunk_size=1000, chunk_overlap=200)
splits = text_splitter.split_documents(docs)

vectorstore = Chroma.from_documents(documents=splits, embedding=HuggingFaceEmbeddings(model_name="sentence-transformers/all-mpnet-base-v2"))

retriever = vectorstore.as_retriever()

prompt = hub.pull("rlm/rag-prompt")
    
model = OllamaLLM(model="llama3.2:1b")

while True:
    print("Enter your question, Enter (N) to end")
    in_question = input()
    if in_question == "N":
        break

    rag_chain = (
        {"context": retriever | format_docs, "question": RunnablePassthrough()}
        | prompt
        | model
        | StrOutputParser()
    )
    print()

    for chunk in rag_chain.stream(in_question):
        print(chunk, end="", flush=True)

    print("\n")
