import cv2
from PIL import Image, ImageTk
import tkinter as tk
from tkinter import ttk
import torch
from torchvision import transforms

from ml import GameObjectModel

class ImageClassifierApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Camera Image Classifier")

        self.init_gui()

        # Load the pre-trained ResNet model
        self.model = GameObjectModel()

        # Define the image transformation
        self.transform = transforms.Compose([
            transforms.Resize((224, 224)),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
        ])

        # Initialize the camera
        self.cap = cv2.VideoCapture(0)
        if not self.cap.isOpened():
            print("Error: Could not open camera.")
            root.destroy()  # Close the application if the camera cannot be opened
            return

        # Schedule the initial call to the update method
        self.root.after(10, self.update)

    def init_gui(self):
        # Create the GUI components
        self.label = ttk.Label(self.root, text="Click 'Capture' to take a picture")
        self.label.pack(pady=10)

        self.canvas = tk.Canvas(self.root, width=224, height=224)
        self.canvas.pack()

        self.btn_capture = ttk.Button(self.root, text="Capture", command=self.take_picture)
        self.btn_capture.pack(pady=10)

        self.result_label = ttk.Label(self.root, text="Prediction: ")
        self.result_label.pack(pady=10)

    def take_picture(self):
        # Capture a frame from the camera
        _, frame = self.cap.read()

        # Convert the OpenCV frame to a PIL Image
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image = Image.fromarray(frame_rgb)

        # Perform inference
        prediction = self.classify_image(image)

        # Display the result
        self.result_label.config(text=f"Prediction: {prediction}")

        # Update the canvas with the captured image
        self.display_captured_image(frame_rgb)

    def display_captured_image(self, frame_rgb):
        # Convert the OpenCV frame to a PhotoImage for display in the Tkinter canvas
        photo = ImageTk.PhotoImage(image=Image.fromarray(frame_rgb))
        self.canvas.photo = photo  # Keep a reference to avoid garbage collection
        self.canvas.create_image(0, 0, anchor=tk.NW, image=photo)

    def classify_image(self, image):
        classes = self.model.CLASSES
        # Transform the image and prepare it for the model
        input_tensor = self.transform(image)
        input_batch = input_tensor.unsqueeze(0).to(self.model.DEVICE)

        # Perform inference
        with torch.no_grad():
            output = self.model(input_batch)

        # Get the predicted class label
        _, predicted_idx = torch.max(output, 1)
        predicted_label = classes[predicted_idx]
        print(predicted_label, predicted_idx)
        return predicted_label

    def update(self):
        # Continuously update the camera feed
        ret, frame = self.cap.read()
        if ret:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            self.display_captured_image(frame)
        else:
            print("Error capturing frame from the camera.")

        # Schedule the next call to the update method
        self.root.after(10, self.update)

    def __del__(self):
        # Release the camera when the application is closed
        if hasattr(self, 'cap') and self.cap.isOpened():
            self.cap.release()

if __name__ == "__main__":
    root = tk.Tk()
    app = ImageClassifierApp(root)
    root.protocol("WM_DELETE_WINDOW", app.__del__)  # Handle the window close event
    root.mainloop()
