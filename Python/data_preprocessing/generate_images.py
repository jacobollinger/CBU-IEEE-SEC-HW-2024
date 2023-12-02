import ffmpeg
import os

def strip_video(path, fps):
    if os.path.isdir(path):
        for i in os.listdir(path):
            strip_video(os.path.join(path, i), fps)
    elif os.path.basename(path) == ".DS_Store":
        # Ignore .DS_Store files
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

def generate_images(fps):
    strip_video("./data/in/videos", fps)

if __name__ == "__main__":
    generate_images(10)
