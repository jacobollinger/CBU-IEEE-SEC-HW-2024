import os
import subprocess


def decompress_data(data_path=os.path.join(".", "data", "in", "ieee"), annotations=True, images=True):
    if annotations:
        print("Decompressing annotations.7z...")
        subprocess.run(["7zz", "x", os.path.join(data_path, "annotations.7z"), "-o" + data_path])
       
    
    if images:
        print("Decompressing images.7z...")
        subprocess.run(["7zz", "x", os.path.join(data_path, "images.7z"), "-o" + data_path])

if __name__ == "__main__":
    decompress_data()