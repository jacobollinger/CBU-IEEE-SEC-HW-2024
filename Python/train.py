try:
    from datetime import datetime
    import torch
    from torch.utils.data import DataLoader, random_split
except ModuleNotFoundError:
    print(
        'Modules are missing, please install the required packages using "pip3 install -r requirements.txt"'
    )

from ml import GameObjectDataset, GameObjectModel

DEVICE = "cuda" if torch.cuda.is_available() else "cpu"

dataset = GameObjectDataset()

train_len = int(len(dataset) * 0.8)
test_len = len(dataset) - train_len

train_dataset, test_dataset = random_split(dataset, [train_len, test_len])

train_loader = DataLoader(train_dataset)
test_loader = DataLoader(test_dataset)

classes = ("small_package", "large_package", "fuel_tank", "thruster")

model = GameObjectModel().to(DEVICE)
try:
    model.load_state_dict(torch.load("model.pth"))
    model.eval()
except FileNotFoundError:
    print("No model found, training from scratch...")

criterion = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.001, momentum=0.9)

epochs = 5

for epoch in range(epochs):
    for i, (images, labels) in enumerate(train_loader):
        images = images.to(DEVICE)
        labels = labels.to(DEVICE)

        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        optimizer.step()

        if i % 1 == 0:
            print(f"Epoch {epoch+1}/{epochs}, Step {i+1}/{len(train_loader)}, Loss: {loss.item():.4f}")

    # File name: model-datetime-epoch-loss.pth
    # Folder name: models
    torch.save(model.state_dict(), f"models/model-{datetime.now().strftime('%Y-%m-%d-%H-%M-%S')}-epoch-{epoch+1}-loss-{loss.item():.4f}.pth")
