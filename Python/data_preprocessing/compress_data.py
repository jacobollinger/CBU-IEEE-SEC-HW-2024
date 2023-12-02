import shutil

shutil.make_archive('data_in', 'zip', './data/in/videos/')
print('next')
shutil.make_archive('data_out', 'zip', 'data/out/models')