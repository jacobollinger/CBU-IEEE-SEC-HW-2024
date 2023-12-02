import gdown

def download_data():
    file_ids = {
        "data_in.zip": "1g7TM9EN-HWMOLRCJQc9CLpDfOD7cvB17",
        "data_out.zip": "1bKNEYkmblU8B9b-39RV-jZckZLpz2xP6"
    }
    for name, id in file_ids.items():
        gdown.download(f"https://drive.google.com/uc?id={id}", f"{name}", quiet=False)

if __name__ == "__main__":
    download_data()





# # Download public file from Google Drive

# import requests
# import os
# import sys

# #* data_in.zip: https://drive.google.com/file/d/1g7TM9EN-HWMOLRCJQc9CLpDfOD7cvB17/view?usp=share_link

# def download_file_from_google_drive(id, destination):
#     URL = "https://docs.google.com/uc?export=download"
#     session = requests.Session()
#     response = session.get(URL, params = {'id': id}, stream = True)
#     token = get_confirm_token(response)
#     if token:
#         params = {'id': id, 'confirm': token}
#         response = session.get(URL, params = params, stream = True)
#     save_response_content(response, destination)
    
# def get_confirm_token(response):
#     for key, value in response.cookies.items():
#         if key.startswith('download_warning'):
#             return value
#     return None

# def save_response_content(response, destination):
#     CHUNK_SIZE = 32768
#     with open(destination, "wb") as f:
#         for chunk in response.iter_content(CHUNK_SIZE):
#             if chunk: # filter out keep-alive new chunks
#                 f.write(chunk)

# if __name__ == "__main__":
#     file_id = '1g7TM9EN-HWMOLRCJQc9CLpDfOD7cvB17'
#     destination = 'data_in2.zip'
#     download_file_from_google_drive(file_id, destination)
#     print("Downloaded data_in.zip from Google Drive")
#     sys.exit(0)