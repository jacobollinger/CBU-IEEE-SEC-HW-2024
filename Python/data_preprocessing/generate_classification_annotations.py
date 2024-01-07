import csv
import os

from Python.modules.model.ml import GameObjectModel

def generate_classification_annotations():
    print("Generating annotations...")
    object_class_to_number = {c: n for n, c in enumerate(GameObjectModel.CLASSES)}

    with open("./data/in/classification_annotations.csv", "w", newline='') as f:
        writer = csv.writer(f)
        for root, _, files in os.walk("./data/in/images/raw"):
            for file in files:
                if file == ".DS_Store":
                    continue
                object_class = os.path.basename(root)
                number = object_class_to_number[object_class]
                # print(f"{file} => {object_class} ({number})")
                writer.writerow([file, object_class, number])

if __name__ == "__main__":
    generate_classification_annotations()