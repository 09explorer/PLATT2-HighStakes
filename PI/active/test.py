
import time

from functions import vision

cam = vision.vision()

while True:

    test = cam.getObjectOffest(vision.color.BLUE)
    print (test)

    #time.sleep(0.1)