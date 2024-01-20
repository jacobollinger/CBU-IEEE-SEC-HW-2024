import os

from Python.data_preprocessing.download_data import download_data
from Python.data_preprocessing.decompress_data import decompress_data
from Python.data_preprocessing.split_data import split_data

data_path = os.path.join(".", "data", "in", "ieee")

download_data(
    annotations=not os.path.exists(os.path.join(data_path, "annotations.7z")),
    images=not os.path.exists(os.path.join(data_path, "images.7z")),
)

decompress_data(
    annotations=not os.path.exists(os.path.join(data_path, "Annotations")), 
    images=not os.path.exists(os.path.join(data_path, "JPEGImages"))
)

split_data(train=0.8, valid=0.2)

print("Setup complete!")
