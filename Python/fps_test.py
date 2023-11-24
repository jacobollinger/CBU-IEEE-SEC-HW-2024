import time
import torch

from ml import GameObjectModel

with torch.no_grad():
    model = GameObjectModel()
    
    start_time = previous_time = time.time()

    iterations = 1000
    for i in range(iterations):
        output = model(torch.rand(1, 3, 224, 224).to(model.DEVICE))
        current_time = time.time()
        
        if i % 10 == 0:
            print(f"FPS: {1 / (current_time - previous_time):4.2f}\tProgress: {(i / iterations * 100):5.2f}%")
            
        previous_time = current_time
        
    end_time = time.time()
    
    print(f"Average FPS: {iterations / (end_time - start_time):4.2f}\tAverage time per frame: {(end_time - start_time) / iterations * 1000:4.2f}ms")
