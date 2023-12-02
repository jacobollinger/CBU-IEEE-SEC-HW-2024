import os

from Python.data_preprocessing.download_data import download_data
from Python.data_preprocessing.decompress_data import decompress_data
from Python.data_preprocessing.generate_images import generate_images
from Python.data_preprocessing.generate_annotations import generate_annotations

# get data:
print("Downloading data...")
download_data()

print("Decompressing data...")
decompress_data()

print("Generating images...")
generate_images()

print("Generating annotations...")
generate_annotations(fps=10)

os.remove("data_in.zip")
os.remove("data_out.zip")
print("Setup complete!")