import os
from pymongo import MongoClient

client = MongoClient("mongodb://localhost:27017")


try:
        db = client["Sample_COBOL"]
        collection = db["Medium"]

        path = os.path.expanduser("~/f24-michelin/docs/COBOL/medium")
        if not os.path.isdir(path):
                raise FileNotFoundError(f"Directory does not exist: {path}")

        for filename in os.listdir(path):
                file_path = os.path.join(path, filename)


                with open(file_path, "r") as file:
                        file_content = file.read()

                cobol_document = {
                        "filename": filename,
                        "content": file_content,
                        "metadata": {
                                "file_size": len(file_content),
                        }
                }

                collection.insert_one(cobol_document)
finally:
        client.close()