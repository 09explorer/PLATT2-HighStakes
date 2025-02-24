from label import label
from indicator import status
import time


def autonSelect(robotData):

    while robotData[label.ALLIANCE.value] == 0:
        time.sleep(0.01)
    
    robotData[label.STATUSLIGHT.value] = status.RUNNING.value

    if robotData[label.ALLIANCE.value] == 1:
        if robotData[label.NAME.value] == 1:
            if robotData[label.AUTON.value] ==1:
                
    
        



















