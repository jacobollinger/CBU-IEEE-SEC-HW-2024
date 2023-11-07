import pip
import subprocess

# install requirements:
pip.main(['install', '-r', 'requirements.txt'])

# get data:
try:
    subprocess.check_call(['git', 'submodule', 'init'])
    subprocess.check_call(['git', 'submodule', 'update'])
    print('Data downloaded successfully')
except subprocess.CalledProcessError as e:
    print('Data download failed:', e)
    raise
