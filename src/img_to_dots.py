import cv2
import sys
import numpy as np

img = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE) 

print(img)

import csv
with open(sys.argv[2], 'w') as f:
     csv.writer(f, delimiter=' ').writerows(img)