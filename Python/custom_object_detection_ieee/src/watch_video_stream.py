# import cv2
# import time

# # Open the video file
# cap = cv2.VideoCapture('./data/out/ieee/inference_outputs/videos/video0.mp4')

# while True:
#     # Try to read the next frame
#     ret, frame = cap.read()

#     print(ret)

#     if ret:
#         # If a frame was read, display it
#         cv2.imshow('Video', frame)

#         # If 'q' is pressed on the keyboard, quit:
#         if cv2.waitKey(1) & 0xFF == ord('q'):
#             break
#     else:
#         # If no frame was read (because it hasn't been written yet), wait a bit
#         time.sleep(0.1)

# # Release the video file and close the window
# cap.release()
# cv2.destroyAllWindows()

import cv2
import socket
import pickle
import struct

# Start a socket
client_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
client_socket.connect(('localhost', 8485))

data = b""
payload_size = struct.calcsize("L")

while True:
    while len(data) < payload_size:
        data += client_socket.recv(4096)

    packed_message_size = data[:payload_size]
    data = data[payload_size:]
    message_size = struct.unpack("L", packed_message_size)[0]

    while len(data) < message_size:
        data += client_socket.recv(4096)

    frame_data = data[:message_size]
    data = data[message_size:]

    # Deserialize frame
    frame = pickle.loads(frame_data)

    # Display the resulting frame
    cv2.imshow('Frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cv2.destroyAllWindows()
