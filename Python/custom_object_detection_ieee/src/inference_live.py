import numpy as np
import cv2
import torch
import os
import time
import argparse
import pathlib
import socket
import pickle
import struct

from model import create_model
from config import GUI, NUM_CLASSES, DEVICE, CLASSES, COLORS, OUT_DIR

np.random.seed(42)

# Construct the argument parser.
parser = argparse.ArgumentParser()
parser.add_argument(
    "-i",
    "--input",
    help="path to video input",
    default="/dev/video0",
)
parser.add_argument("--imgsz", default=640, type=int, help="image resize shape")
parser.add_argument("--threshold", default=0.25, type=float, help="detection threshold")
args = vars(parser.parse_args())

# os.makedirs(f"{OUT_DIR}/inference_outputs/videos", exist_ok=True)

# COLORS = [[0, 0, 0], [255, 0, 0], [255, 0, 0], [255, 0, 0], [255, 0, 0], [255, 0, 0], [255, 0, 0], [255, 0, 0], [255, 0, 0]]

# Load the best model and trained weights.
model = create_model(num_classes=NUM_CLASSES, size=640)
checkpoint = torch.load(f"{OUT_DIR}/e273_BEST/best_model.pth", map_location=DEVICE)
model.load_state_dict(checkpoint["model_state_dict"])
model.to(DEVICE).eval()

# Define the detection threshold.
detection_threshold = 0.2

server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server_socket.bind(("localhost", 8485))
server_socket.listen()

client_socket, addr = server_socket.accept()

cap = cv2.VideoCapture(args["input"])

if cap.isOpened() == False:
    print("Error while trying to read video. Please check path again")

# Get the frame width and height.
frame_width = int(cap.get(3))
frame_height = int(cap.get(4))

save_name = str(pathlib.Path(args["input"])).split(os.path.sep)[-1].split(".")[0]
print(save_name)
# Define codec and create VideoWriter object .
out = cv2.VideoWriter(
    f"{OUT_DIR}/inference_outputs/videos/{save_name}.mp4",
    cv2.VideoWriter_fourcc(*"mp4v"),
    30,
    (frame_width, frame_height),
)

frame_count = 0  # To count total frames.
total_fps = 0  # To get the final frames per second.

# Read until end of video.
while cap.isOpened():
    # Capture each frame of the video.
    ret, frame = cap.read()
    if ret:
        image = frame.copy()
        if args["imgsz"] is not None:
            image = cv2.resize(image, (args["imgsz"], args["imgsz"]))
        image = cv2.cvtColor(image, cv2.COLOR_BGR2RGB).astype(np.float32)
        # Make the pixel range between 0 and 1.
        image /= 255.0
        # Bring color channels to front (H, W, C) => (C, H, W).
        image_input = np.transpose(image, (2, 0, 1)).astype(np.float32)
        # Convert to tensor.
        image_input = torch.tensor(image_input, dtype=torch.float).cuda()
        # Add batch dimension.
        image_input = torch.unsqueeze(image_input, 0)
        # Get the start time.
        start_time = time.time()
        # Predictions
        with torch.no_grad():
            outputs = model(image_input.to(DEVICE))
        end_time = time.time()

        # Get the current fps.
        fps = 1 / (end_time - start_time)
        # Total FPS till current frame.
        total_fps += fps
        frame_count += 1

        # Load all detection to CPU for further operations.
        outputs = [{k: v.to("cpu") for k, v in t.items()} for t in outputs]
        # Carry further only if there are detected boxes.
        if len(outputs[0]["boxes"]) != 0:
            boxes = outputs[0]["boxes"].data.numpy()
            scores = outputs[0]["scores"].data.numpy()
            # Filter out boxes according to `detection_threshold`.
            boxes = boxes[scores >= args["threshold"]].astype(np.int32)
            draw_boxes = boxes.copy()
            # Get all the predicted class names.
            pred_classes = [CLASSES[i] for i in outputs[0]["labels"].cpu().numpy()]

            # Draw the bounding boxes and write the class name on top of it.
            for j, box in enumerate(draw_boxes):
                class_name = pred_classes[j]
                color = COLORS[CLASSES.index(class_name)]
                # Rescale boxes.
                xmin = int((box[0] / image.shape[1]) * frame.shape[1])
                ymin = int((box[1] / image.shape[0]) * frame.shape[0])
                xmax = int((box[2] / image.shape[1]) * frame.shape[1])
                ymax = int((box[3] / image.shape[0]) * frame.shape[0])
                cv2.rectangle(frame, (xmin, ymin), (xmax, ymax), color[::-1], 3)
                cv2.putText(
                    frame,
                    class_name,
                    (xmin, ymin - 5),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.8,
                    color[::-1],
                    2,
                    lineType=cv2.LINE_AA,
                )
        cv2.putText(
            frame,
            f"{fps:.0f} FPS",
            (15, 25),
            cv2.FONT_HERSHEY_SIMPLEX,
            1,
            (0, 255, 0),
            2,
            lineType=cv2.LINE_AA,
        )

        data = pickle.dumps(frame)
        message_size = struct.pack("L", len(data))
        client_socket.sendall(message_size + data)

        if GUI:
            cv2.imshow("image", frame)
        out.write(frame)
        # Press `q` to exit.
        # if cv2.waitKey(1) & 0xFF == ord("q"):
        #    break

    else:
        break

# Release VideoCapture().
cap.release()
# Close all frames and video windows.
cv2.destroyAllWindows()

# Calculate and print the average FPS.
avg_fps = total_fps / frame_count
print(f"Average FPS: {avg_fps:.3f}")
