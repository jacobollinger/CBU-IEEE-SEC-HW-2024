import torch

GUI = False

BATCH_SIZE = 30  # Increase / decrease according to GPU memory.
RESIZE_TO = 640  # Resize the image for training and transforms.
NUM_EPOCHS = 1000  # Number of epochs to train for.
NUM_WORKERS = 4  # Number of parallel workers for data loading.


# DEVICE = "cuda" if torch.cuda.is_available() else "mps" if torch.backends.mps.is_available() else "cpu"
DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

# training images and XML files directory
TRAIN_DIR = "./data/in/ieee/train"

# validation images and XML files directory
VALID_DIR = "./data/in/ieee/valid"

with open("./data/in/ieee/labelmap.txt", "r") as f:
    label_map = [
        [line.split(":")[0], [int(s) for s in line.split(":")[1].split(",")]]
        for line in f.readlines()[1:]
    ]

# classes: 0 index is reserved for background
CLASSES = [sublist[0] for sublist in label_map]
IGNORED_CLASSES = [
    "small_package_delivery_zone",
    "large_package_delivery_zone",
    "fuel_tank_pickup_zone",
    "crater_line"
]

NUM_CLASSES = len(CLASSES)

# COLORS = [sublist[1] for sublist in label_map]
COLORS = [
    (0, 0, 0),          # #000000
    (140, 120, 240),    # #8c78f0
    (181, 171, 143),    # #b5ab8f
    (255, 96, 55),      # #ff6037
    (245, 147, 49),     # #f59331
    (255, 0, 0),        # #ff0000
    (0, 0, 255),        # #0000ff
    (36, 179, 83),      # #24b353
    (255, 255, 255),    # #ffffff
]

# whether to visualize images after creating the data loaders
VISUALIZE_TRANSFORMED_IMAGES = False

# location to save model and plots
OUT_DIR = "./data/out/ieee"
