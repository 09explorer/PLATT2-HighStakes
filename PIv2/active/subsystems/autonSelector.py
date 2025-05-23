from subsystems.label import label
from subsystems.indicator import status
import time

import autons.blue.pink.comp1.start
import autons.blue.pink.test1.start
import autons.blue.purple.comp1.start
import autons.blue.purple.test2.start
import autons.red.pink.comp1.start
import autons.red.pink.skills.start
import autons.red.purple.comp1.start
import autons.red.purple.skills.start


def autonSelect(robotData):

    while robotData[label.RUN.value] == 0: 

        #print(robotData[label.RUN.value], flush=True)
        
        time.sleep(0.001)
    
    robotData[label.STATUSLIGHT.value] = status.RUNNING.value

    if robotData[label.ALLIANCE.value] == 1:
        if robotData[label.NAME.value] == 1:
            if robotData[label.AUTON.value] == 1:
                autons.red.pink.comp1.start.start(robotData)
            else:
                autons.red.pink.skills.start.start(robotData)
        else:
            if robotData[label.AUTON.value] == 1:
                autons.red.purple.comp1.start.start(robotData)
            else:
                autons.red.purple.skills.start.start(robotData)
    else: 
        if robotData[label.NAME.value] == 1:
            if robotData[label.AUTON.value] == 1:
                autons.blue.pink.comp1.start.start(robotData)
            else:
                autons.blue.pink.test1.start.start(robotData)
        else:
            if robotData[label.AUTON.value] == 1:
                autons.blue.purple.comp1.start.start(robotData)
            else:
                autons.blue.purple.test2.start.start(robotData)
                
    
        



















