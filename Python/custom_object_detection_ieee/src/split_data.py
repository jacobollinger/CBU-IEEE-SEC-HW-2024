import os
import random
import shutil

training_percentage = 0.8

data_dir = './data/in/IEEE/test'
train_dir = data_dir + '/train'
valid_dir = data_dir + '/valid'

if __name__ == '__main__':
    os.makedirs(train_dir, exist_ok=True)
    os.makedirs(valid_dir, exist_ok=True)
    
    for file in os.listdir(data_dir):
        if file.endswith('.PNG'):
            if random.random() < training_percentage:
                print('Copying ' + file + ' to ' + train_dir)
                shutil.copy(data_dir + '/' + file, train_dir + '/' + file)
                shutil.copy(data_dir + '/' + file.replace('.PNG', '.xml'), train_dir + '/' + file.replace('.PNG', '.xml'))
            else:
                print('Copying ' + file + ' to ' + valid_dir)
                shutil.copy(data_dir + '/' + file, valid_dir + '/' + file)
                shutil.copy(data_dir + '/' + file.replace('.PNG', '.xml'), valid_dir + '/' + file.replace('.PNG', '.xml'))