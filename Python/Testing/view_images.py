# from actuators import Wheels, Arm
from ml import GameObjectModel, GameObjectDataset
import torch
from torch.utils.data import DataLoader
import matplotlib.pyplot as plt
import numpy as np
import math

def main():
    dataset = GameObjectDataset()
    dataloader = DataLoader(dataset, batch_size=4, shuffle=True, num_workers=4)
    model = GameObjectModel()


    for images, labels in dataloader:
        show_batch(images, labels)

    # for i_batch, sample_batched in enumerate(dataloader):
    #     # display images
    #     imshow(torchvision.utils.make_grid(sample_batched))
    # pass

def show_batch(images, labels):
    classes = ("packages", "thruster", "fuel_tank")

    figure = plt.figure()
    rows = cols = math.ceil(math.sqrt(len(images)))
    for i in range(len(images)):
        img, label = denormalize(images[i]), classes[labels[i].item()]
        figure.add_subplot(rows, cols, i+1)
        plt.title(label)
        plt.axis("off")
        img = img.permute(1, 2, 0)
        plt.imshow(img.squeeze())
    plt.show()

def denormalize(tensor):
    mean = torch.tensor([0.485, 0.456, 0.406]).view(3, 1, 1)
    std = torch.tensor([0.299, 0.224, 0.225]).view(3, 1, 1)
    return tensor * std + mean

if __name__ == "__main__":
    main()