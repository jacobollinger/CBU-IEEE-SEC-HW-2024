from ffmpeg import FFmpeg
import os

def strip_video(path, fps):
    if os.path.isdir(path):
        if os.path.basename(path) == ".ignore":
            return
        for i in os.listdir(path):
            strip_video(os.path.join(path, i), fps)
    elif os.path.basename(path) == ".DS_Store":
        # Ignore .DS_Store files
        pass
    else:
        file = os.path.basename(path)
        basename, _ = os.path.splitext(file)
        object_class = os.path.basename(os.path.dirname(path))

        if not os.path.exists(f"./data/in/images/raw/{object_class}"):
            print(f"Creating directory data/in/images/raw/{object_class}")
            os.makedirs(f"./data/in/images/raw/{object_class}")

        if fps is None:
            print(f"Stripping {path} to ./data/in/images/raw/{object_class}/{basename}_%d.jpg")
            FFmpeg().input(path).output(f"./data/in/images/raw/{object_class}/{basename}_%d.jpg").execute()
        else:
            print(f"Stripping {path} to ./data/in/images/raw/{object_class}/{basename}_%d.jpg at {fps} fps")
            FFmpeg().input(path).output(f"./data/in/images/raw/{object_class}/{basename}_%d.jpg", vf=f"fps={fps}").execute()

def generate_images(fps=None):
    print("Generating images...")
    strip_video("./data/in/videos", fps)

if __name__ == "__main__":
    generate_images()
