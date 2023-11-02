import torch
import torch.nn as nn
import torch.nn.functional as F
from torchvision.io import read_image
import torchvision.transforms as transforms
import pandas as pd
import os

ANNOTATIONS_FILE = "data/annotations.csv"
IMAGE_PATH = "data/images"


class GameObjectDataset(torch.utils.data.Dataset):
    def __init__(self, image_set, transform=None, target_transform=None):
        self.IMAGE_LABELS = pd.read_csv(ANNOTATIONS_FILE)
        self.IMAGE_DIR = IMAGE_PATH + "/" + image_set
        self.transform = transform
        self.target_transform = target_transform

    def __len__(self):
        return len(self.IMAGE_LABELS)

    def __getitem__(self, index):
        image_path = os.path.join(self.IMAGE_DIR, self.IMAGE_LABELS.iloc[index, 0])
        image = read_image(image_path)
        label = self.IMAGE_LABELS.iloc[index, 1]
        if self.transform:
            image = self.transform(image)
        if self.target_transform:
            label = self.target_transform(label)
        return image, label


class GameObjectDataLoader(torch.utils.data.DataLoader):
    # TODO: Implement data loader
    pass


class GameObjectCNNModel(nn.Module):
    def __init__(self):
        super(GameObjectCNNModel, self).__init__()
        """
        self.conv1 = nn.Conv2d(3,,)

        in_channels: 3 (RGB)
        TODO out_channels: ?
        TODO kernel_size: ?
        """

        # TODO: Implement convolutional layers
        """
        pool = nn.MaxPool2d(?, ?)
        conv2 = nn.Conv2d(?, ?, ?)
        self.fc1 = nn.Linear(?, ?)
        self.fc?
        """

    def forward(self, x):
        # TODO: Implement forward pass
        """
        x = ?

        ...

        return x
        """
