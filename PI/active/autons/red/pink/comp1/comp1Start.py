import functions.vision as vision
import communication as com

def comp1Start(robotData):
    
    cam = vision.vision()
                 
    while True:
        #print("running", flush=True)
        offset = cam.getObjectOffest(vision.color.BLUE)

        if offset is None:
            robotData[com.label.LEFTVEL.value] = 0
            robotData[com.label.RIGHTVEL.value] = 0
            print("NONE", flush=True)

        else: 
            robotData[com.label.LEFTVEL.value] =    offset[1]*0.2
            robotData[com.label.RIGHTVEL.value] =  -offset[1]*0.2
            print(offset, flush=True)
    