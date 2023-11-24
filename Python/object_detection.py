import torch
import torchvision
from torchvision import transforms as T
import cv2
import cvzone

model = torchvision.models.detection.ssd300_vgg16(pretrained = True)

model.eval()

classnames = []
with open('./Python/classes.txt', 'r') as f:
    classnames = f.read().splitlines()


image = cv2.imread('./Python/img.jpeg')
img = image.copy()

imgtransform = T.ToTensor()
image = imgtransform(image)

with torch.no_grad():
    ypred = model([image])
    bbox, scores, labels = ypred[0]['boxes'], ypred[0]['scores'], ypred[0]['labels']
    nums = torch.argwhere(scores > 0.60).shape[0]
    for i in range(nums):
        x, y, w, h = bbox[i].numpy().astype('int')
        cv2.rectangle(img, (x,y), (w,h), (0,0,255), 5)
        classname = labels[i].numpy().astype('int')
        classdetected = classnames[classname-1]
        #print(classdetected)
        cvzone.putTextRect(img, classdetected, [x-50,y-50], scale=1,border=1)


cv2.imshow('frame', img)
cv2.waitKey(0)
