import os

from Python.data_preprocessing.download_data import download_data
from Python.data_preprocessing.decompress_data import decompress_data
from Python.data_preprocessing.generate_images import generate_images
from Python.data_preprocessing.generate_annotations import generate_annotations

# get data:
print("Downloading data...")
download_data(
    "https://mega.nz/file/ITs1gACR#3W8t6PR2inOByLBI5450d9ebAcd06_9eCOY24p8QCLA",
    "https://mega.nz/file/VT9WQSaA#XGYL9DlEbiCd8HwrLdyTT8uhP_H-X58JYmlclGQKyHE",
)

print("Decompressing data...")
decompress_data()

print("Generating images...")
generate_images(fps=10)

print("Generating annotations...")
generate_annotations()

# os.remove("data_in.zip")
# os.remove("data_out.zip")
print("Setup complete!")
