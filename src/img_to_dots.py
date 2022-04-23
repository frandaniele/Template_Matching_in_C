import cv2
import sys
import csv

img = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE) 

with open(sys.argv[2], 'w') as f:
     size = str(img.shape[0]) + " " + str(img.shape[1]) + "\n"
     f.write(size)
     csv.writer(f, delimiter=' ').writerows(img)