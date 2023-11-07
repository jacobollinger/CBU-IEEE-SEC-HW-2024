try:
    import torch
    import torch.nn as nn
    import torch.nn.functional as F
    from torchvision.io import read_image
    import torchvision.transforms as transforms
    import pandas as pd
    import os
except ModuleNotFoundError:
    print(
        'Modules are missing, please run the "python3 setup.py" script or install the required packages using"pip3 install -r requirements.txt"'
    )

ANNOTATIONS_FILE = "data/annotations.csv"
IMAGES_PATH = "data/images"


class GameObjectDataset(torch.utils.data.Dataset):
    """
    A dataset class for the game object dataset.
    """

    def __init__(self, images_path=IMAGES_PATH, transform=None, target_transform=None):
        """
        image_path: Path to image directory.
        transform: A function/transform that takes in an image and returns a transformed version.
        target_transform: A function/transform that takes in the target and transforms it.
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
        
        image_path = os.path.join(self.IMAGE_DIR, self.IMAGE_LABELS.iloc[index, 0])
        image = read_image(image_path)
        label = self.IMAGE_LABELS.iloc[index, 1]
        if self.transform:
            image = self.transform(image)
        if self.target_transform:
            label = self.target_transform(label)
        return image, label


# class GameObjectDataLoader(torch.utils.data.DataLoader):
#     super(GameObjectDataLoader, self).__init__()
#     # TODO: Implement data loader
#     pass


class GameObjectCNNModel(nn.Module):
    """
    A CNN model for the game object dataset.
    """

    def __init__(self):
        """
        Initializes the model.
        """
        super(GameObjectCNNModel, self).__init__()
        # self.conv1 = nn.Conv2d(3,,)
        """
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
        """
        Performs a forward pass on the model.
        """
        # TODO: Implement forward pass
        """
        x = ?

        ...

        return x
        """
