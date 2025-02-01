import time
import communication as com
import functions.basicMove as basicMove
import functions.vision as vision


def comp1Start(robotData):
    
    cam = vision.vision()
 
    cam.getGoal(robotData)
    time.sleep(1)
    cam.chase(robotData,  vision.color.BLUE)
    robotData[com.label.HOOKS.value] = 100
    time.sleep(5)

    robotData[com.label.HOOKS.value] = 0
    robotData[com.label.INTAKE.value] = 0

    pass


