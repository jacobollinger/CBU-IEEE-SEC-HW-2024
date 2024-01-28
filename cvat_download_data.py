import cvat_sdk
import multiprocessing
import threading
from tqdm import tqdm
import os
import xml.etree.ElementTree as ET
import zipfile

base_dir = os.path.join(".", "cvat_downloads")

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
            tqdm.write(f"Skipping {task.name} (task {task.id}) because it has already been downloaded")
        pbar.update(1)
        
        if not os.path.exists(os.path.join(base_dir, f"task_{task.id}")):
            file = f"task_{task.id}.zip"
            tqdm.write(f"Unzipping {file}...")
            with zipfile.ZipFile(os.path.join(base_dir, "downloads", file), "r") as zip_ref:
                zip_ref.extractall(path=os.path.join(base_dir, f"task_{task.id}"))
        else:
            tqdm.write(f"Skipping {task.name} (task {task.id}) because it has already been unzipped")
        pbar.update(1)
    finally:
        # Release the semaphore
        semaphore.release()

with cvat_sdk.make_client(host="http://localhost:8080", credentials=('jacob', 'bollinger')) as client:
    tasks = client.tasks.list()
    pbar = tqdm(total=len(tasks) * 2, desc="Tasks", dynamic_ncols=True, position=0, leave=True)
    threads = []
    for task in tasks:
        # if task.status != "completed":
        #     tqdm.write(f"Skipping {task.name} (task {task.id}) because it is not completed")
        #     continue

        thread = threading.Thread(target=download_and_extract, args=(task,))
        thread.start()
        threads.append(thread)

    # Wait for all threads to complete
    for thread in threads:
        thread.join()
        
pbar.close()

tasks = []
        
for folder in os.listdir(base_dir):
    if folder.startswith("task_"):
        task = {folder: {"images": [], "annotations": []}}
        for dirpath, dirnames, filenames in os.walk(os.path.join(base_dir, folder)):
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
        print(f"Processing {key}...")
        for annotation, image in zip(task[key]["annotations"], task[key]["images"]):
            tree = ET.parse(annotation)
            root = tree.getroot()

            root.find("filename").text = f"frame_{frame:06d}.PNG"
            tree.write(annotation)
            
            os.rename(annotation, os.path.join(os.path.dirname(annotation), "../../../data/in/ieee/Annotations", f"frame_{frame:06d}.xml"))
            os.rename(image, os.path.join(os.path.dirname(image), "../../../data/in/ieee/JPEGImages", f"frame_{frame:06d}.PNG"))
            
            # task_n_frame000000 -> frame000000
            # frame_ma
            
            frame += 1
           
        os.system(f"rm -rf {base_dir}/{key}")

    
print(f"Processed {frame} frames")

pbar.close()
