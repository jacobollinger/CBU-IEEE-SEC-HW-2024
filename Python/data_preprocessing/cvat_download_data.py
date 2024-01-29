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


def download_and_extract(client, task, pbar):
    # Acquire a semaphore
    semaphore.acquire()

    try:
        task_dir = os.path.join(base_dir, f"task_{task.id}")
        task_zip = os.path.join(base_dir, "downloads", f"task_{task.id}.zip")

        if not os.path.exists(task_dir):
            if not os.path.exists(task_zip):
                tqdm.write(f"Downloading task_{f'{task.id}:':<4}...")
                client.tasks.retrieve(task.id).export_dataset(
                    "PASCAL VOC 1.1", task_zip
                )
            else:
                tqdm.write(
                    f"Downloading task_{f'{task.id}:':<4} Skipping because it has already been downloaded"
                )

            tqdm.write(f"Extracting task_{f'{task.id}:':<4} ...")
            with zipfile.ZipFile(task_zip, "r") as zip_ref:
                zip_ref.extractall(path=task_dir)
            # os.remove(task_zip)
            if not os.path.exists(os.path.join(base_dir, "labelmap.txt")):
                os.rename(
                    os.path.join(base_dir, f"task_{task.id}", "labelmap.txt"),
                    os.path.join(base_dir, "labelmap.txt"),
                )
        else:
            tqdm.write(
                f"Extracting task_{f'{task.id}:':<4} Skipping because it has already been extracted"
            )
    finally:
        pbar.update(1)
        # Release the semaphore
        semaphore.release()


def cvat_download_data(host="http://localhost:8080", credentials=auth):
    if os.path.exists(os.path.join(base_dir, "installed_tasks.txt")):
        with open(os.path.join(base_dir, "installed_tasks.txt"), "r") as f:
            installed_tasks = [int(line.strip()) for line in f.readlines()]
    else:
        installed_tasks = []

    with cvat_sdk.make_client(host=host, credentials=credentials) as client:
        tasks = client.tasks.list()
        tasks = sorted(tasks, key=lambda task: task.id)
        pbar = tqdm(
            total=len(tasks) - len(installed_tasks),
            desc="Downloading Tasks",
            dynamic_ncols=True,
            position=0,
            leave=True
        )
        threads = []
        for task in tasks:
            if task.status != "completed":
                tqdm.write(
                    f"Skipping task_{f'{task.id}:':<4} it is not completed (status: {task.status})"
                )
                pbar.update(1)
                continue
            if task.id in installed_tasks:
                tqdm.write(
                    f"Skipping task_{f'{task.id}:':<4} it has already been installed"
                )
                continue

            thread = threading.Thread(
                target=download_and_extract, args=(client, task, pbar)
            )
            thread.start()
            threads.append(thread)

        # Wait for all threads to complete
        for thread in threads:
            thread.join()

    pbar.close()

    tasks = {}

    print("Getting tasks...")
    for folder in os.listdir(base_dir):
        if folder.startswith("task_"):
            task = {"images": [], "annotations": []}
            for dirpath, _, filenames in os.walk(os.path.join(base_dir, folder)):
                for file in filenames:
                    if file.endswith(".xml"):
                        task["annotations"].append(os.path.join(dirpath, file))
                    elif file.endswith(".PNG"):
                        task["images"].append(os.path.join(dirpath, file))

            # sort the images and annotations
            task["images"] = sorted(task["images"])
            task["annotations"] = sorted(task["annotations"])
            tasks[folder] = task.copy()

    tasks = {key: tasks[key] for key in sorted(tasks.keys())}

    for task, task_values in tasks.items():
        tqdm.write(f"Installing: {task}...", end="")
        for annotation, image in zip(task_values["annotations"], task_values["images"]):
            tree = ET.parse(annotation)
            root = tree.getroot()

            # frame000000 -> task_n_frame000000
            # frame = f"{task}_frame{root.find('filename').text[5:-4]}"
            frame = f"{task}_{root.find('filename').text[:-4]}"

            root.find("filename").text = f"{frame}.PNG"
            tree.write(annotation)

            # Ensure the destination directories exist
            os.makedirs(os.path.join(base_dir, "Annotations"), exist_ok=True)
            os.makedirs(os.path.join(base_dir, "JPEGImages"), exist_ok=True)

            os.rename(annotation, os.path.join(base_dir, "Annotations", f"{frame}.xml"))
            os.rename(image, os.path.join(base_dir, "JPEGImages", f"{frame}.PNG"))


        installed_tasks.append(task.split("_")[1])
        shutil.rmtree(os.path.join(base_dir, task))
        tqdm.write("done")

    pbar.close()
    print(f"Processed {frame} frames")

    with open(os.path.join(base_dir, "installed_tasks.txt"), "w") as f:
        for task in installed_tasks:
            f.write(f"{task}\n")


if __name__ == "__main__":
    cvat_download_data()
