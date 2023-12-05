from zipfile import ZipFile


def decompress_data():
    print("Decompressing data_in.zip...")
    with ZipFile("./data/data_in.zip", 'r') as zip_ref:
        zip_ref.extractall("./data/in/videos")

    print("Decompressing data_out.zip...")
    with ZipFile("./data/data_out.zip", 'r') as zip_ref:
        zip_ref.extractall("./data/out/models")

if __name__ == "__main__":
    decompress_data()