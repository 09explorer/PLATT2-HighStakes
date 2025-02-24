import time
from gpiozero import LED # type: ignore
from label import label
from enum import Enum

class status(Enum):

    LINKWAIT = 0
    STANDBY = 1
    ERROR = 2

def indicator(robotData):
    
    green = LED(17)
    red = LED(27)

    startTime = time.time()
    oldStatus = robotData[label.LIGHTSTATUS.value]

    while True:

        if oldStatus != robotData[label.LIGHTSTATUS.value]:
            green.off()
            red.off()
        
        if robotData[label.LIGHTSTATUS.value] == 0:
            
            if int((time.time()-startTime)*10) % 2 == 0:
                green.on()
            else:
                green.off()
        
        if robotData[label.LIGHTSTATUS.value] == 1:
            
            green.on()

        if robotData[label.LIGHTSTATUS.value] == 2:
            
            if int((time.time()-startTime)*10) % 2 == 0:
                red.on()
            else:
                red.off()
        

        oldStatus = robotData[label.LIGHTSTATUS.value]
        time.sleep(0.1)
    
    
    
    
