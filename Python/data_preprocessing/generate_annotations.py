import csv
import os

def generate_annotations():
    type_to_number = {
        "small_package": 0,
        "thruster": 1,
        "large_package": 2,
        "fuel_tank_thruster_assembly": 3,
        "fuel_tank": 4,
    }

    with open("./data/in/annotations.csv", "w") as f:
        writer = csv.writer(f)
        for root, dirs, files in os.walk("./data/in/images/raw"):
            for file in files:
                if file == ".DS_Store":
                    continue
                path = os.path.join(root, file)
                type = os.path.basename(os.path.dirname(path))
                number = type_to_number.get(type)
                print(f"{file} => {type} ({number})")
                writer.writerow([file, type, number])

if __name__ == "__main__":
    generate_annotations()