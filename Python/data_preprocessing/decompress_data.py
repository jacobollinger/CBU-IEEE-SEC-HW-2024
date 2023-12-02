from zipfile import ZipFile


def decompress_data():
    with ZipFile("./data_in.zip", 'r') as zip_ref:
        zip_ref.extractall("./data/in/videos")
        
    with ZipFile("./data_out.zip", 'r') as zip_ref:
        zip_ref.extractall("./data/out/models")

if __name__ == "__main__":
    decompress_data()