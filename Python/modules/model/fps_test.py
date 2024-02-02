import random
import time
import torch

from ml import GameObjectDataset, GameObjectModel

with torch.no_grad():
    dataset = GameObjectDataset()
    model = GameObjectModel()
    
    print("Device: ", GameObjectModel.DEVICE)
    
    iterations = 100
    random_ints = [random.randint(0, len(dataset) - 1) for i in range(iterations)]

    start_time = previous_time = time.time()

    for i in random_ints:
        output = model(dataset[i][0].unsqueeze(0).to(GameObjectModel.DEVICE))
        current_time = time.time()
        if i % 10 == 0:
            print(f"FPS: {1 / (current_time - previous_time):4.2f}\tTime per frame: {(current_time - previous_time) * 1000:4.2f}ms")

        previous_time = current_time
        
    end_time = time.time()
    
    print(f"Average FPS: {iterations / (end_time - start_time):4.2f}\tAverage time per frame: {(end_time - start_time) / iterations * 1000:4.2f}ms")
