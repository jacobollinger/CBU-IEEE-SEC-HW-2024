from mega import Mega
import os


def download_data(data_path=os.path.join(".", "data", "in", "ieee"), annotations=True, images=True):
    annotations = "https://mega.nz/file/JO9DWYDb#AMv8-ahtmkFrZCUXoffc9n6-odNrLtLiRAV_mUi0upo"
    images = "https://mega.nz/file/kb9hhI5J#sYwqPdKbCWUagSnTt94HIFrnjWtOLC1havaJVHHMtzU"
    
    mega = Mega()
    session = mega.login()

    os.makedirs(data_path, exist_ok=True)

    if annotations and not os.path.exists(os.path.join(data_path, "annotations.7z")):
        print("Downloading annotations.7z...")
        session.download_url(annotations, data_path)

    if images and not os.path.exists(os.path.join(data_path, "images.7z")):
        print("Downloading images.7z...")
        session.download_url(images, data_path)

if __name__ == "__main__":
    download_data()
