import random
import time
import torch

from ml import GameObjectDataset, GameObjectModel

with torch.no_grad():
    dataset = GameObjectDataset()
    model = GameObjectModel()
    
    start_time = previous_time = time.time()

    iterations = 100
    for i in range(iterations):
        rand = random.randint(0, len(dataset) - 1)
        output = model(dataset[rand][0].unsqueeze(0))
        current_time = time.time()
        if i % 10 == 0:
            print(f"FPS: {1 / (current_time - previous_time):4.2f}\tProgress: {(i / iterations * 100):5.2f}%")

        previous_time = current_time
        
    end_time = time.time()
    
    print(f"Average FPS: {iterations / (end_time - start_time):4.2f}\tAverage time per frame: {(end_time - start_time) / iterations * 1000:4.2f}ms")
