import cvat_sdk
import multiprocessing
import shutil
import threading
from tqdm import tqdm
import os
import xml.etree.ElementTree as ET
import zipfile

auth = ("jacob", "bollinger")
base_dir = os.path.join(".", "data", "in", "ieee")

os.makedirs(os.path.join(base_dir, "downloads"), exist_ok=True)

# Create a semaphore for 4 threads
semaphore = threading.Semaphore(multiprocessing.cpu_count())

def download_and_extract(task):
    # Acquire a semaphore
    semaphore.acquire()
    
    try:
        if not os.path.exists(os.path.join(base_dir, "downloads", f"task_{task.id}.zip")):
                tqdm.write(f"Downloading annotations for {task.name} (task {task.id})...")
                client.tasks.retrieve(task.id).export_dataset("PASCAL VOC 1.1", os.path.join(base_dir, "downloads", f"task_{task.id}.zip"))
        else:
            tqdm.write(f"Skipping download for {task.name} (task {task.id}) because it has already been downloaded")
        
        if not os.path.exists(os.path.join(base_dir, f"task_{task.id}")):
            file = f"task_{task.id}.zip"
            tqdm.write(f"Unzipping {file}...")
            with zipfile.ZipFile(os.path.join(base_dir, "downloads", file), "r") as zip_ref:
                zip_ref.extractall(path=os.path.join(base_dir, f"task_{task.id}"))
            os.remove(os.path.join(base_dir, "downloads", file))
        else:
            tqdm.write(f"Skipping unzip for {task.name} (task {task.id}) because it has already been unzipped")
        
        installed.append(task.id)
    finally:
        pbar.update(1)
        # Release the semaphore
        semaphore.release()

if os.path.exists(os.path.join(base_dir, "installed.txt")):
    with open(os.path.join(base_dir, "installed.txt"), "r") as f:
        installed = [int(line.strip()) for line in f.readlines()]
else:
    installed = []

def cvat_download_data(host="http://localhost:8080", credentials=auth):
    with cvat_sdk.make_client(host=host, credentials=credentials) as client:
        tasks = client.tasks.list()
        pbar = tqdm(total=len(tasks), desc="Downloading Tasks", dynamic_ncols=True, position=0, leave=True)
        threads = []
        for task in tasks:
            if task.status != "completed":
                tqdm.write(f"Skipping {task.name} (task {task.id}) because it is not completed")
                pbar.update(1)
                continue
            if task.id in installed:
                tqdm.write(f"Skipping {task.name} (task {task.id}) because it has already been installed")
                pbar.update(1)
                continue

            thread = threading.Thread(target=download_and_extract, args=(task,))
            thread.start()
            threads.append(thread)

        # Wait for all threads to complete
        for thread in threads:
            thread.join()
            
    pbar.close()

    tasks = []

    print("Getting tasks...") 
    for folder in os.listdir(base_dir):
        if folder.startswith("task_"):
            task = {folder: {"images": [], "annotations": []}}
            for dirpath, _, filenames in os.walk(os.path.join(base_dir, folder)):
                for file in filenames:
                    if file.endswith(".xml"):
                        task[folder]["annotations"].append(os.path.join(dirpath, file))
                    elif file.endswith(".PNG"):
                        task[folder]["images"].append(os.path.join(dirpath, file))
            
            # sort the images and annotations
            task[folder]["images"] = sorted(task[folder]["images"])
            task[folder]["annotations"] = sorted(task[folder]["annotations"])
            tasks.append(task)

    tasks = sorted(tasks, key=lambda x: list(x.keys())[0])

    # map task frames to frame numbers
    frame_map = {}
    frame = 0

    for task in tasks:
        for key in task:
            tqdm.write(f"Processing {key}...")
            for annotation, image in zip(task[key]["annotations"], task[key]["images"]):
                tree = ET.parse(annotation)
                root = tree.getroot()
                
                # task_n_frame000000 -> frame000000
                # {key}_{root.find("filename").text.split(".")[0]} -> frame_{frame:06d}
                frame_map[f"{key}_{root.find('filename').text.split('.')[0]}"] = f"frame_{frame:06d}"

                root.find("filename").text = f"frame_{frame:06d}.PNG"
                tree.write(annotation)
                
                # Ensure the destination directories exist
                os.makedirs(os.path.join(base_dir, "Annotations"), exist_ok=True)
                os.makedirs(os.path.join(base_dir, "JPEGImages"), exist_ok=True)
                
                os.rename(annotation, os.path.join(base_dir, "Annotations", f"frame_{frame:06d}.xml"))
                os.rename(image, os.path.join(base_dir, "JPEGImages", f"frame_{frame:06d}.PNG"))
                
                frame += 1

            shutil.rmtree(os.path.join(base_dir, key))

    pbar.close()
    print(f"Processed {frame} frames")

    with open(os.path.join(base_dir, "installed.txt"), "w") as f:
        for task in installed:
            f.write(f"{task}\n")

if __name__ == "__main__":
    cvat_download_data()
