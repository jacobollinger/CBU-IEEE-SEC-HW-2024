import datetime
import time
import torch
from torch.utils.data import DataLoader, random_split
from torchvision import transforms

from ml import GameObjectDataset, GameObjectModel

start_time = time.time()

tfs = transforms.Compose([
    transforms.Resize((224)),
    transforms.ToTensor(),
    transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225])
])

dataset = GameObjectDataset(transform=tfs)

train_len = int(len(dataset) * 0.8)
test_len = len(dataset) - train_len

train_dataset, test_dataset = random_split(dataset, [train_len, test_len])

batch_size = 64
train_dataloader = DataLoader(train_dataset, batch_size=batch_size, shuffle=True)
test_dataloader = DataLoader(test_dataset, batch_size=batch_size, shuffle=True)

classes = ("", "small_package", "thruster", "large_package", "fuel_tank_thruster_assembly", "fuel_tank")

model = GameObjectModel(load_from_file=True)

criterion = torch.nn.CrossEntropyLoss()
optimizer = torch.optim.SGD(model.parameters(), lr=0.001, momentum=0.9)

epochs = 10
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
            print(f"Epoch {epoch+1}/{epochs}, Step {i+1}/{len(train_dataloader)}, Loss: {loss.item():.4f}, ETA: {str(datetime.timedelta(seconds=int(average_step_time * steps_remaining)))}")

    model.epoch_save(epoch, total_loss / len(train_dataloader))

print("Finished training!")

with torch.no_grad():
    end_time_train = time.time()
    print(f"Training time: {str(datetime.timedelta(seconds=int(end_time_train - start_time)))}")
    
    correct = 0
    total = 0
    for images, labels in test_dataloader:
        images = images.to(model.DEVICE)
        labels = labels.to(model.DEVICE)

        outputs = model(images)
        _, predicted = torch.max(outputs.data, 1)
        # print(f"Predicted: {classes[predicted.item()]}, Actual: {classes[labels.item()]}, Correct: {(predicted == labels).item()}")
        for i in range(len(predicted)):
            print(f"Predicted: {classes[predicted[i].item()]}, Actual: {classes[labels[i].item()]}, Correct: {(predicted[i] == labels[i]).item()}")
        total += labels.size(0)
        correct += (predicted == labels).sum().item()
    
    accuracy = 100 * correct / total
    print(f"Accuracy: {accuracy}%")
    
    end_time_test = time.time()
    print(f"Training time: {str(datetime.timedelta(seconds=int(end_time_train - start_time)))}")
    print(f"Testing time: {str(datetime.timedelta(seconds=int(end_time_test - end_time_train)))}")
    print(f"Total time: {str(datetime.timedelta(seconds=int(end_time_test - start_time)))}")
    
    model.save(postfix=f"_a{accuracy:.2f}")
