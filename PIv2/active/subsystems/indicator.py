import time
from gpiozero import LED # type: ignore
from subsystems.label import label
from enum import Enum

class status(Enum):


    OFF = 0
    DISCONNECTED = 1
    PION = 2
    CONNECTED = 3
    ERROR = 4
    RUNNING = 5
    FINNISHED = 6
    STANDBY = 7

def indicator(robotData):
    
    red = LED(17)
    green = LED(18)

    startTime = time.time()
    oldStatus = robotData[label.STATUSLIGHT.value]

    while True:

        if oldStatus != robotData[label.STATUSLIGHT.value] or robotData[label.STATUSLIGHT.value] == status.OFF.value:
            green.off()
            red.off()
        
        if robotData[label.STATUSLIGHT.value] == status.DISCONNECTED.value:
            
            if int((time.time()*2-startTime)) % 2 == 0:
                red.on()
            else:
                red.off()
        
        if robotData[label.STATUSLIGHT.value] == status.CONNECTED.value:
            
            if int((time.time()*2-startTime)) % 2 == 0:
                green.on()
            else:
                green.off()
        
        if robotData[label.STATUSLIGHT.value] == status.STANDBY.value:
            
            green.on()

        if robotData[label.STATUSLIGHT.value] == status.RUNNING.value:
            
            if int((time.time()*10-startTime)) % 2 == 0:
                green.on()
            else:
                green.off()

        if robotData[label.STATUSLIGHT.value] == status.ERROR.value:
            
            if int((time.time()*10-startTime)) % 2 == 0:
                red.on()
            else:
                red.off()

        if robotData[label.STATUSLIGHT.value] == status.FINNISHED.value:
            
            green.on()
            red.on()

        if robotData[label.STATUSLIGHT.value] == status.PION.value:
            
            if int((time.time()*10-startTime)) % 2 == 0:
                red.on()
                green.on()
            else:
                red.off()
                green.off()


        
        oldStatus = robotData[label.STATUSLIGHT.value]
        time.sleep(0.01)
    
    
    
    
