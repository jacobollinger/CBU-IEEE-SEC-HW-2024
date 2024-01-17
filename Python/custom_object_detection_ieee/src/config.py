import torch

BATCH_SIZE = 12 # Increase / decrease according to GPU memeory.
RESIZE_TO = 640 # Resize the image for training and transforms.
NUM_EPOCHS = 10 # Number of epochs to train for.
NUM_WORKERS = 4 # Number of parallel workers for data loading.


#DEVICE = "cuda" if torch.cuda.is_available() else "mps" if torch.backends.mps.is_available() else "cpu"
DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

# training images and XML files directory
TRAIN_DIR = './data/in/IEEE/train'
# validation images and XML files directory
VALID_DIR = './data/in/IEEE/valid'
# classes: 0 index is reserved for background
CLASSES = [
    'background', 'small_package', 'large_package', 'fuel_tank', 'thruster','small_package_delivery_zone','large_package_delivery_zone','fuel_tank_pickup_zone','crater_line'
]
NUM_CLASSES = len(CLASSES)
# whether to visualize images after crearing the data loaders
VISUALIZE_TRANSFORMED_IMAGES = False
# location to save model and plots
OUT_DIR = './Python/custom_object_detection_ieee/outputs'
