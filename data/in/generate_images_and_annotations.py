import csv
import ffmpeg
import os
import subprocess

fps = 10

def strip_video(path):
    if os.path.isdir(path):
        for i in os.listdir(path):
            strip_video(os.path.join(path, i))
    elif(os.path.basename(path) == ".DS_Store"):
        pass
    else:
        file = os.path.basename(path)
        basename, _ = os.path.splitext(file)

        # get the last directory in the path
        type = os.path.basename(os.path.dirname(path))

        if not os.path.exists(f"./data/in/images/raw/{type}"):
            print(f"Creating directory data/in/images/raw/{type}")
            os.makedirs(f"./data/in/images/raw/{type}")

        print(f"Stripping {path} to ./data/in/images/raw/{type}/{basename}_%d.jpg")
        
        ffmpeg.input(path).output(f"./data/in/images/raw/{type}/{basename}_%d.jpg", vf=f"fps={fps}", pix_fmt="yuvj420p").run()

def generate_annotations():
    type_to_number = {
        "small_package": 0,
        "thruster": 1,
        "large_package": 2,
        "fuel_tank_thruster_assembly": 3,
        "fuel_tank": 4,
    }

    with open("./data/in/annotations2.csv", "w") as f:
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
    # strip_video("./data/in/videos/processed")
    generate_annotations()
