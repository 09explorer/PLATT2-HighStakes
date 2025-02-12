import time
import communication as com
from functions import basicMove

def blueSide(robotData):

    
    basicMove.turnToHeading(robotData, 245)
 
    basicMove.targetMove(robotData, (50,98), True, linVel=20)
    
    robotData[com.label.CLAMP.value] = 1
    time.sleep(0.5)

    robotData[com.label.HOOKS.value] = 100

    basicMove.turnToHeading(robotData, 180)




    basicMove.targetMove(robotData, (26,96), linVel=30)



    basicMove.turnToHeading(robotData, 90)



    basicMove.targetMove(robotData, (24,117), linVel=30)



    basicMove.turnToHeading(robotData, 135)

    robotData[com.label.INTAKEPISTON.value] = 0
    robotData[com.label.HOOKS.value] = 0
    
    


    basicMove.targetMove(robotData, (10, 142-10), linVel=30)
    robotData[com.label.INTAKEPISTON.value] = 1
    robotData[com.label.HOOKS.value] = 100

    
    time.sleep(0.5)


    basicMove.targetMove(robotData, (24, 118), True, linVel=30)
    
    time.sleep(0.5)

    basicMove.targetMove(robotData, (10, 142 - 10), linVel=30)

    time.sleep(0.5)

    basicMove.targetMove(robotData, (24, 118), True, linVel=30)

    time.sleep(0.5)

    basicMove.relitiveTurn(robotData, 180)

    basicMove.targetMove(robotData, (10, 142-10), True, linVel=30)

    robotData[com.label.HOOKS.value] = 0
    robotData[com.label.CLAMP.value] = 0

    basicMove.targetMove(robotData, (24, 118), linVel=30)

