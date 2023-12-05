import os

from Python.data_preprocessing.download_data import download_data
from Python.data_preprocessing.decompress_data import decompress_data
from Python.data_preprocessing.generate_images import generate_images
from Python.data_preprocessing.generate_annotations import generate_annotations

if not os.path.exists("./data/data_in.zip"):
    download_data(data_out=False)
if not os.path.exists("./data/data_out.zip"):
    download_data(data_in=False)

decompress_data()

generate_images(fps=10)

generate_annotations()

print("Setup complete!")
