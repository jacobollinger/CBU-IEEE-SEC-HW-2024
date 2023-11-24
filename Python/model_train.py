from datetime import datetime
import time
import torch
from torch.utils.data import DataLoader, random_split

from ml import GameObjectDataset, GameObjectModel

start_time = time.time()

dataset = GameObjectDataset()

train_len = int(len(dataset) * 0.8)
test_len = len(dataset) - train_len

train_dataset, test_dataset = random_split(dataset, [train_len, test_len])

train_dataloader = DataLoader(train_dataset)
test_dataloader = DataLoader(test_dataset)

classes = ("package", "thruster", "fuel_tank")

model = GameObjectModel(load_from_file=False)

criterion = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.001, momentum=0.9)

epochs = 5
total_steps = 0
step_time = start_time
average_step_time = 0

for epoch in range(epochs):
    total_loss = 0
    for i, (images, labels) in enumerate(train_dataloader):
        
        images = images.to(model.DEVICE)
        labels = labels.to(model.DEVICE)

        optimizer.zero_grad()
        outputs = model(images)
        loss = criterion(outputs, labels)
        loss.backward()
        total_loss += loss.item()
        optimizer.step()

        total_steps += 1
        previous_step_time = step_time
        step_time = time.time()
        average_step_time = average_step_time * (total_steps - 1) / total_steps + (step_time - previous_step_time) / total_steps
    
        if i % 1 == 0:
            steps_remaining = (epochs - epoch) * len(train_dataloader) - i
            print(f"Epoch {epoch+1}/{epochs}, Step {i+1}/{len(train_dataloader)}, Loss: {loss.item():.4f}, ETA: {datetime.utcfromtimestamp(average_step_time * steps_remaining).strftime('%H:%M:%S')}")

    model.epoch_save(epoch, total_loss / len(train_dataloader))

print("Finished training!")

with torch.no_grad():
    end_time_train = time.time()
    print(f"Training time: {datetime.utcfromtimestamp(end_time_train - start_time).strftime('%H:%M:%S')}")
    
    correct = 0
    total = 0
    for images, labels in test_dataloader:
        images = images.to(model.DEVICE)
        labels = labels.to(model.DEVICE)

        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        print(f"Predicted: {classes[predicted.item()]}, Actual: {classes[labels.item()]}, Correct: {predicted == labels}")
        total += labels.size(0)
        correct += (predicted == labels).sum().item()
    
    print(f"Accuracy: {100 * correct / total}%")
    
    end_time_test = time.time()
    print(f"Training time: {datetime.utcfromtimestamp(end_time_train - start_time).strftime('%H:%M:%S')}")
    print(f"Testing time: {datetime.utcfromtimestamp(end_time_test - end_time_train).strftime('%H:%M:%S')}")
    print(f"Total time: {datetime.utcfromtimestamp(end_time_test - start_time).strftime('%H:%M:%S')}")
