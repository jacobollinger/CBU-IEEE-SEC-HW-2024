import torch

from ml import GameObjectDataset, GameObjectDataLoader, GameObjectCNNModel

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

train_dataset = GameObjectDataset("train")
test_dataset = GameObjectDataset("test")
valid_dataset = GameObjectDataset("valid")

train_loader = GameObjectDataLoader(train_dataset)
test_loader = GameObjectDataLoader(test_dataset)
valid_loader = GameObjectDataLoader(valid_dataset)

classes = ("small package", "large package", "fuel tank", "thruster")

model = GameObjectCNNModel().to(DEVICE)
try:
    model.load_state_dict(torch.load("model.pth"))
    model.eval()
except FileNotFoundError:
    print("No model found, training from scratch...")

# TODO: set criterion and optimizer

def train(epochs, batch_size=4, learning_rate=0.001):

    for epoch in range(epochs):
        for i, (images, labels) in enumerate(train_loader):
            images = images.to(DEVICE)
            labels = labels.to(DEVICE)

            # TODO: implement training loop
    
    torch.save(model.state_dict(), "model.pth")
