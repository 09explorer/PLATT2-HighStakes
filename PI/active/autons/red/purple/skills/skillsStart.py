import time
import communication as com
import functions.basicMove as basicMove

def skillsStart(robotData):

    robotData[com.label.HEADINGOFFSET.value] = 90
    robotData[com.label.XPOSOFFSET.value] = 48
    robotData[com.label.YPOSOFFSET.value] = 18


    robotData[com.label.INTAKE.value] = 100
    
    basicMove.targetMove(robotData, (48,49))

    basicMove.turnToHeading(robotData, 0)

    basicMove.targetMove(robotData, (28,48), True)

    robotData[com.label.CLAMP.value] = 1
    time.sleep(0.2)
    
    robotData[com.label.HOOKS.value] = 100
    basicMove.turnToHeading(robotData, 270)

    basicMove.targetMove(robotData, (22,24))

    time.sleep(1)
   
    basicMove.turnToHeading(robotData, 225)

    time.sleep(1)

    basicMove.targetMove(robotData, (6,6))

    time.sleep(1)

    basicMove.targetMove(robotData, (18,18), True)
    time.sleep(1)

    basicMove.relitiveTurn(robotData, 180)
    time.sleep(1)

    basicMove.targetMove(robotData, (10,10), True)
    time.sleep(1)

    robotData[com.label.CLAMP.value] = 0
    time.sleep(1)


    basicMove.targetMove(robotData, (18,18))

    time.sleep(1)
    
    pass