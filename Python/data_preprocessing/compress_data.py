import shutil

def compress_data():
    shutil.make_archive('data_in', 'zip', './data/in/videos/')
    shutil.make_archive('data_out', 'zip', 'data/out/models')

if __name__ == "__main__":
    compress_data()