import json
import os
import random
import subprocess
import tqdm
import xml.etree.ElementTree as ET


def xml_contains_object(xml_file):
    tree = ET.parse(xml_file)

    for obj in tree.getroot().iter("object"):
        if list(obj):
            return True

    return False


def generate_split_data_json(data_path, train, valid, test):
    df = {"split": [train, valid, test], "train": [], "valid": [], "test": []}
    for file in os.listdir(os.path.join(data_path, "Annotations")):
        if file.endswith(".xml") and xml_contains_object(
            os.path.join(data_path, "Annotations", file)
        ):
            rand = random.random()
            basename = os.path.splitext(file)[0]
            if rand < train:
                df["train"].append(basename)
            elif rand < train + valid:
                df["valid"].append(basename)
            else:
                df["test"].append(basename)

    with open(os.path.join(data_path, "data_split.json"), "w") as f:
        json.dump(df, f)

    return df

def split_data(
    data_path=os.path.join(".", "data", "in", "ieee"),
    train=0,
    valid=0,
    test=0,
    force=False,
):
    if train + valid + test != 1:
        raise ValueError("train + valid + test must equal 1")
        return
    
    if force:
        if os.path.exists(os.path.join(data_path, "data_split.json")):
            subprocess.run(["rm", os.path.join(data_path, "data_split.json")])
        if os.path.exists(os.path.join(data_path, "train")):
            subprocess.run(["rm", "-rf", os.path.join(data_path, "train")])
        if os.path.exists(os.path.join(data_path, "valid")):
            subprocess.run(["rm", "-rf", os.path.join(data_path, "valid")])
        if os.path.exists(os.path.join(data_path, "test")):
            subprocess.run(["rm", "-rf", os.path.join(data_path, "test")])
    
    if not os.path.exists(os.path.join(data_path, "data_split.json")):
        print("No data_split.json found, generating new split...")
        df = generate_split_data_json(data_path, train, valid, test)
    else:
        with open(os.path.join(data_path, "data_split.json"), "r") as f:
            df = json.load(f)
    
    if not force and not train == df["split"][0] and not valid == df["split"][1] and not test == df["split"][2]:
        raise f"Data split give ({train}, {valid}, {test}) does not match data split in data_split.json ({df['split'][0]}, {df['split'][1]}, {df['split'][2]}) to override this error, set force=True"
    
    if train > 0: os.makedirs(os.path.join(data_path, "train"), exist_ok=True)
    if valid > 0: os.makedirs(os.path.join(data_path, "valid"), exist_ok=True)
    if test > 0: os.makedirs(os.path.join(data_path, "test"), exist_ok=True)
        
    df.pop("split")
    
    pbar = tqdm.tqdm(total=2*sum([len(files) for files in df.values()]), dynamic_ncols=True, position=0, leave=True)
        
    for data_split, files in df.items():
        for file in files:
            if not os.path.exists(os.path.join(data_path, data_split, file + ".xml")):
                subprocess.run(["mv", os.path.join(data_path, "Annotations", file + ".xml"), os.path.join(data_path, data_split)])
            pbar.update(1)
            
            if not os.path.exists(os.path.join(data_path, data_split, file + ".PNG")):
                subprocess.run(["mv", os.path.join(data_path, "JPEGImages", file + ".PNG"), os.path.join(data_path, data_split)])
            pbar.update(1)




if __name__ == "__main__":
    split_data(train=0.8, valid=0.2)
