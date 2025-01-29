import time
import functions.vision as vision
import cv2
import numpy as np

if __name__ == '__main__':
    
    
    
    
    
 
    
    
    cam = vision.vision()

    target =  cam.getObjectOffest(vision.color.RED)

    while target is not None and target[1]>10:

        target = cam.getObjectOffest(vision.color.RED)

        
        
        

