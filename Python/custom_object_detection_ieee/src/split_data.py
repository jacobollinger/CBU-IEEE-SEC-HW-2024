import os
import random
import shutil

def copy_files(src_dir, dest_dir, file, annotation_file):
    print(f'Copying {file} to {dest_dir}')
    shutil.copy(os.path.join(src_dir, file), os.path.join(dest_dir, file))
    shutil.copy(os.path.join(src_dir, annotation_file), os.path.join(dest_dir, annotation_file))

training_percentage = 0.8

data_dir = './data/in/IEEE'
image_dir = os.path.join(data_dir, 'JPEGImages')
annotation_dir = os.path.join(data_dir, 'Annotations')
train_dir = os.path.join(data_dir, 'train')
valid_dir = os.path.join(data_dir, 'valid')

if __name__ == '__main__':
    os.makedirs(train_dir, exist_ok=True)
    os.makedirs(valid_dir, exist_ok=True)
    
    for file in os.listdir(image_dir):
        annotation_file = os.path.splitext(file)[0] + '.xml'
        
        if random.random() < training_percentage:
            copy_files(image_dir, train_dir, file, annotation_file)
        else:
            copy_files(image_dir, valid_dir, file, annotation_file)
