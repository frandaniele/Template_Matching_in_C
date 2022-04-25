import cv2
import sys
import csv

img = cv2.imread(sys.argv[1], cv2.IMREAD_GRAYSCALE) 
#(x, y) = (row, col) = (img.shape[0], img.shape[1])

with open(sys.argv[2], 'w') as f:
     size = str(img.shape[0]) + " " + str(img.shape[1]) + "\n"
     f.write(size)
     csv.writer(f, delimiter=' ').writerows(img)

# Naming a window
cv2.namedWindow("Resized_Window", cv2.WINDOW_NORMAL)
  
# Using resizeWindow()
cv2.resizeWindow("Resized_Window", 1000, 800)
  
# Displaying the image
cv2.imshow("Resized_Window", img)
cv2.waitKey(0)
cv2.destroyWindow('i')