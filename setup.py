import pip
import subprocess

from Python.data_preprocessing.generate_images import generate_images
from Python.data_preprocessing.generate_annotations import generate_annotations
from Python.data_preprocessing.decompress_data import decompress_data

# install requirements:
# pip.main(['install', '-r', 'requirements.txt'])

# get data:
print("Decompressing data...")
decompress_data()
print("Generating images...")
generate_images()
print("Generating annotations...")
generate_annotations()
