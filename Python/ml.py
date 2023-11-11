try:
    import torch
    import torch.nn as nn
    import torch.nn.functional as F
    import torchvision
    from torchvision.io import read_image
    import torchvision.transforms as transforms
    import pandas as pd
    from PIL import Image
    import os
except ModuleNotFoundError:
    print(
        'Modules are missing, please run the "python3 setup.py" script or \
        install the required packages using"pip3 install -r requirements.txt"'
    )

ANNOTATIONS_FILE = "./data/annotations.csv"
IMAGES_PATH = "./data/images/raw"

transform = transforms.Compose([
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.299, 0.224, 0.225])
])

class GameObjectDataset(torch.utils.data.Dataset):
    """
    A dataset class for the game object dataset.
    """

    def __init__(self, images_path=IMAGES_PATH, transform=transform, target_transform=None):
        """
        image_path: Path to image directory.
        transform: A function/transform that takes in an image and returns a 
            transformed version.
        target_transform: A function/transform that takes in the target and 
            transforms it.
        """
        self.IMAGE_LABELS = pd.read_csv(ANNOTATIONS_FILE)
        self.IMAGE_DIR = images_path
        self.transform = transform
        self.target_transform = target_transform

    def __len__(self):
        """
        Returns the length of the dataset.
        """
        return len(self.IMAGE_LABELS)

    def __getitem__(self, index):
        """
        Returns the data sample at index "index".
        """
        # if torch.is_tensor(index):
        #     index = index.tolist()

        image_path = os.path.join(self.IMAGE_DIR, self.IMAGE_LABELS.iloc[index, 1], self.IMAGE_LABELS.iloc[index, 0])
        image = Image.open(image_path)
        label = self.IMAGE_LABELS.iloc[index, 2]
        if self.transform:
            image = self.transform(image)
        if self.target_transform:
            label = self.target_transform(label)
        return image, label

class GameObjectModel(nn.Module):
    """
    A model for the game object dataset.
    """

    def __init__(self):
        """
        Initializes the model.
        """
        super(GameObjectModel, self).__init__()
        self.resnet = torchvision.models.resnet50(pretrained=True) #? maybe change to a different resnet model
        self.resnet.fc = nn.Linear(self.resnet.fc.in_features, 4)

    def forward(self, x):
        return self.resnet(x)
