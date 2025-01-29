import communication as com
from enum import Enum
import math
import cv2
import numpy as np

class color(Enum):
    RED = 1
    BLUE = 2

class vision:

    def __init__(self):
        
        self.cam = cv2.VideoCapture(0)
        self.xsize = 1280
        self.ysize =  720
        
        self.cam.set(cv2.CAP_PROP_FRAME_WIDTH, self.xsize)
        self.cam.set(cv2.CAP_PROP_FRAME_HEIGHT, self.ysize)

        params = cv2.SimpleBlobDetector_Params()
        params.filterByArea = True
        params.minArea = 1500/4
        params.maxArea = self.xsize*self.ysize
        params.filterByCircularity = False
        params.filterByConvexity = False
        params.filterByInertia = False
        params.blobColor = 255

        self.detector = cv2.SimpleBlobDetector_create(params)

        self.center = [self.xsize/2, self.ysize]

        self.kernal = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5, 5))

    def getObjectOffest(self, wantedColor):
        
        _, img = self.cam.read()
        image = cv2.cvtColor(img, cv2.COLOR_BGR2HSV) 


        match wantedColor:

            case color.RED:
                lower_color = np.array([95,100,100]) 
                upper_color = np.array([105,255,255]) 

            case color.BLUE:
                lower_color = np.array([95,50,50]) 
                upper_color = np.array([105,255,255]) 

        mask = cv2.inRange(image, lower_color, upper_color)   
        mask = cv2.bitwise_and(image, image, mask = mask)

        mask = cv2.cvtColor(mask, cv2.COLOR_HSV2BGR) 
        mask = cv2.cvtColor(mask, cv2.COLOR_BGR2GRAY) 
        
        #blur = cv2.GaussianBlur(mask, (11,11), 0)
        canny = cv2.Canny(mask, 100, 170, 5)
        
        dialate = cv2.dilate(canny, self.kernal, iterations=2)
        #dialate = canny
        #close = cv2.morphologyEx(dialate, cv2.MORPH_CLOSE, (7,7), iterations=8) 
    
        #th, thresh = cv2.threshold(dialate, 127, 255, cv2.THRESH_BINARY)

        # Copy the thresholded image
        im_floodfill = dialate.copy()

        ## Mask used to flood filling.
        ## NOTE: the size needs to be 2 pixels bigger on each side than the input image
        h, w = dialate.shape[:2]
        size = np.zeros((h+2, w+2), np.uint8)

        cv2.floodFill(im_floodfill, size, (0,0), 255)
        cv2.floodFill(im_floodfill, size, ((int)(self.xsize-5),(int)(self.ysize-5)), 255)

        im_floodfill_inv = cv2.bitwise_not(im_floodfill)

        im_out = dialate | im_floodfill_inv

        keypoints = self.detector.detect(im_out)

        #im_out = cv2.drawKeypoints(im_out, keypoints, np.array([]), (0, 0, 255), cv2.DRAW_MATCHES_FLAGS_DRAW_RICH_KEYPOINTS)
        #cv2.imshow("BlobDetection", im_out)
        #
        #if cv2.waitKey(1) == ord('q'):
        #    cv2.destroyWindow("BlobDetection")
            

        targetList = []

        if keypoints:
            for x in keypoints:
                targetList.append([math.sqrt((self.center[0] - x.pt[0])**2 + (self.center[1] - x.pt[1])**2), (math.atan2(self.center[1]-x.pt[1], self.center[0] - x.pt[0])-math.pi/2)*(180/math.pi)])

            min_row = 0
            min_value = targetList[0][0]

            for i in range(1, len(targetList)):
                if targetList[i][0] < min_value:
                    min_value = targetList[i][0]
                    min_row = i
    
            target = targetList[min_row]
    
            return target
            
        else:
            return None
    
    def chase(self, robotData, wantedColor, kpLin = 20):

        target = self.getObjectOffest(wantedColor)

        if target is None:
            return
        
        while target[1] < 10 and target is not None:

            robotData[com.label.LEFTVEL.value] = -target[1]*0.5
            robotData[com.label.RIGHTVEL.value] = target[1]*0.5

            target = self.getObjectOffest(wantedColor)
        
        if target is None:
            return

        while target is not None:

            robotData[com.label.LEFTVEL.value] = -kpLin * target[1]*0.5
            robotData[com.label.RIGHTVEL.value] = kpLin * target[1]*0.5

            target = self.getObjectOffest(wantedColor)
        

