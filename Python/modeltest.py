import tkinter as tk
from tkinter import ttk
from PIL import Image, ImageTk
import cv2
import torch
from torchvision import transforms
from ml import GameObjectModel

class ImageClassifierApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Camera Image Classifier")

        self.init_gui()

        # Load the pre-trained ResNet model
        self.model = GameObjectModel(True)

        # Define the image transformation
        self.transform = transforms.Compose([
            transforms.Resize((224, 224)),
            transforms.ToTensor(),
            transforms.Normalize(mean=[0.485, 0.456, 0.406], std=[0.229, 0.224, 0.225]),
        ])

        # Initialize the camera
        self.cap = cv2.VideoCapture(0)
        self.update()

    def init_gui(self):
        # Create the GUI components
        self.label = ttk.Label(self.root, text="Click 'Capture' to take a picture")
        self.label.pack(pady=10)

        self.canvas = tk.Canvas(self.root, width=300, height=300)
        self.canvas.pack()

        self.btn_capture = ttk.Button(self.root, text="Capture", command=self.take_picture)
        self.btn_capture.pack(pady=10)

        self.result_label = ttk.Label(self.root, text="Prediction: ")
        self.result_label.pack(pady=10)

    def take_picture(self):
        # Capture a frame from the camera
        ret, frame = self.cap.read()

        # Convert the OpenCV frame to a PIL Image
        frame_rgb = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
        image = Image.fromarray(frame_rgb)

        # Perform inference
        prediction = self.classify_image(image)

        # Display the result
        self.result_label.config(text=f"Prediction: {prediction}")

    def classify_image(self, image):
        classes = ("package", "thruster", "fuel_tank")
        # Transform the image and prepare it for the model
        input_tensor = self.transform(image)
        input_batch = input_tensor.unsqueeze(0)

        # Perform inference
        with torch.no_grad():
            output = self.model(input_batch)

        # Get the predicted class label
        _, predicted_idx = torch.max(output, 1)
        predicted_label = classes[predicted_idx]

        return predicted_label

    def update(self):
        # Continuously update the camera feed
        ret, frame = self.cap.read()
        if ret:
            frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
            image = Image.fromarray(frame)
            photo = ImageTk.PhotoImage(image=image)
            self.canvas.create_image(0, 0, anchor=tk.NW, image=photo)
            self.root.after(10, self.update)

if __name__ == "__main__":
    root = tk.Tk()
    app = ImageClassifierApp(root)
    root.mainloop()
