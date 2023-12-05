from mega import Mega
import os
import shutil


def download_data(data_path="./data", data_in=True, data_out=True):
    data_in_link = "https://mega.nz/file/ITs1gACR#3W8t6PR2inOByLBI5450d9ebAcd06_9eCOY24p8QCLA"
    data_out_link = "https://mega.nz/file/VT9WQSaA#XGYL9DlEbiCd8HwrLdyTT8uhP_H-X58JYmlclGQKyHE"
    
    mega = Mega()
    session = mega.login()

    os.makedirs(data_path, exist_ok=True)
    
    if data_in:
        print("Downloading data_in.zip...")
        if os.path.exists(f"{data_path}/in"):
            shutil.rmtree(f"{data_path}/in")
        session.download_url(data_in_link, data_path)
    
    if data_out:
        print("Downloading data_out.zip...")
        if os.path.exists(f"{data_path}/out"):
            shutil.rmtree(f"{data_path}/out")
        session.download_url(data_out_link, data_path)
        
if __name__ == "__main__":
    download_data()
