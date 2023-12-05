import ffmpeg
import shutil
import os

def compress_data():
    print("Formatting videos...")
    for root, _, files in os.walk('./data/in/videos'):
        for file in files:
            if file.casefold().endswith(".mp4") or file.casefold().endswith(".mov"):
                input_video = ffmpeg.input(f"{root}/{file}")
                file_name, extension = os.path.splitext(os.path.basename(file))
                ffmpeg.output(input_video, f"{root}/{file_name}_na{extension}", **{"c:v": "copy", "an": None}).run()
                os.remove(f"{root}/{file}")
                os.rename(f"{root}/{file_name}_na{extension}", f"{root}/{file}")
    
    
    print("Compressing Video Data")
    os.remove('data_in.zip')
    shutil.make_archive('data_in', 'zip', './data/in/videos/')
    print("Compressing Model Data")
    os.remove('data_out.zip')
    shutil.make_archive('data_out', 'zip', 'data/out/models')

if __name__ == "__main__":
    compress_data()