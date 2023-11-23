from datetime import datetime
import torch
import torch.nn as nn
import torch.nn.functional as F
import torchvision
import torchvision.transforms as transforms
import pandas as pd
from PIL import Image
import glob
import os


ANNOTATIONS_FILE = "./data/annotations.csv"
IMAGES_PATH = "./data/images/raw"

transform = transforms.Compose(
    [
        transforms.ToTensor(),
        transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.299, 0.224, 0.225]),
    ]
)


class GameObjectDataset(torch.utils.data.Dataset):
    """
    A dataset class for the game object dataset.
    """

    def __init__(
        self, images_path=IMAGES_PATH, transform=transform, target_transform=None
    ):
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

        image_path = os.path.join(
            self.IMAGE_DIR,
            self.IMAGE_LABELS.iloc[index, 1],
            self.IMAGE_LABELS.iloc[index, 0],
        )
        image = Image.open(image_path).convert("RGB")
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

    def __init__(self, load_from_file=True, file_path=None):
        """
        Initializes the model.
        """
        super(GameObjectModel, self).__init__()
        self.resnet = torchvision.models.resnet50(
            pretrained=True
        )  # ? maybe change to a different resnet model
        self.resnet.fc = nn.Linear(self.resnet.fc.in_features, 4)

        if load_from_file:
            self.load(path=file_path)

    def forward(self, x):
        return self.resnet(x)

    def save(self, path=None, postfix=""):
        if path is None:
            path = (
                f"models/model_{datetime.now().strftime('%Y%m%d_%H%M%S') + postfix}.pth"
            )

        #! make sure models/ directory exists
        os.makedirs("models", exist_ok=True)

        torch.save(self.state_dict(), path)

        print(f"Model saved to {path}")

    def epoch_save(self, epoch, loss):
        name = f"model_{datetime.now().strftime('%Y%m%d_%H%M%S')}"
        path = f"models/{name}_e{epoch}_l{loss:.3f}.pth"
        self.save(path)

    def load(self, path=None):
        if path is None:
            # load latest model
            # format: model_20210907_142912-e1-a0.75.pth
            files = sorted(glob.glob("models/*.pth"))

            if len(files) == 0:
                print("No models found in models/ directory")
                return self

            path = files[-1]

        try:
            self.load_state_dict(torch.load(path))
            self.eval()
            print(f"Model loaded from {path}")
        except FileNotFoundError:
            print(f"Model not found at {path}")

        return self
