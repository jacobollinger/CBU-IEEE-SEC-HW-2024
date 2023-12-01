import ffmpeg
import os

fps = 1

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

if __name__ == "__main__":
    strip_video("./data/in/videos")
