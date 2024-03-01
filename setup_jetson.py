import os
import subprocess

subprocess.check_call(["sudo", "apt", "install", "-y", "libopenblas-base", "libopenmpi-dev", "libomp-dev", "python3-pip", "python3-venv"])
subprocess.check_call(["python3", "-m", "pip", "install", "--upgrade", "pip"])
subprocess.check_call(["python3", "-m", "venv", ".venv"])

subprocess.check_call(["mkdir", "-p", ".install_jetson_requirements"])
os.chdir(".install_jetson_requirements")

# Jetpack 5.1.2 torch 2.1.0
subprocess.check_call(["wget", "https://developer.download.nvidia.com/compute/redist/jp/v512/pytorch/torch-2.1.0a0+41361538.nv23.06-cp38-cp38-linux_aarch64.whl", "-O", "torch-2.1.0a0+41361538.nv23.06-cp38-cp38-linux_aarch64.whl"])
subprocess.check_call(["git", "clone", "--branch", "v0.16.1", "https://github.com/pytorch/vision.git"])

# Jetpack 6.0 torch 2.1.0
# subprocess.check_call(["wget", "https://nvidia.box.com/shared/static/0h6tk4msrl9xz3evft9t0mpwwwkw7a32.whl", "-O", "torch-2.1.0a0+41361538-cp38-cp38-linux_aarch64.whl"])
# subprocess.check_call(["git", "clone", "--branch", "v0.16.1", "https://github.com/pytorch/vision.git"])

subprocess.check_call(["../.venv/bin/pip3", "install", "Cython<3", "numpy", "setuptools", "torch-2.1.0a0+41361538.nv23.06-cp38-cp38-linux_aarch64.whl"])
os.chdir("vision")
# subprocess.check_call(["../../.venv/bin/python3", "setup.py", "install"])
subprocess.check_call(["../../.venv/bin/python3", "setup.py", "build", "-j6"])
subprocess.check_call(["../../.venv/bin/python3", "setup.py", "install"])

os.chdir("..")
subprocess.check_call(["../.venv/bin/pip3", "install", "-r", "../requirements.txt", "-r", "../requirements_jetson_extras.txt", "-r", "vision/docs/requirements.txt"])

os.chdir("..")
subprocess.check_call(["rm", "-rf", ".install_jetson_requirements"])
