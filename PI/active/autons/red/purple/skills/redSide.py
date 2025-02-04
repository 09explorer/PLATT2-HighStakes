
from functions import basicMove
import communication as com
import time

def redSide(robotData):

    basicMove.targetMove(robotData, (48,47))
    
    basicMove.turnToHeading(robotData, 0)

    basicMove.targetMove(robotData, (26,45), True)

    robotData[com.label.CLAMP.value] = 1
    
    basicMove.turnToHeading(robotData, 270)

    robotData[com.label.HOOKS.value] = 100

    basicMove.targetMove(robotData, (22,24))
    
    #time.sleep(0.1)
   
    basicMove.turnToHeading(robotData, 225)

    #time.sleep(0.1)

    basicMove.targetMove(robotData, (8,8))

    #time.sleep(0.1)

    basicMove.targetMove(robotData, (18,18), True)
    
    time.sleep(1)

    basicMove.relitiveTurn(robotData, 180)    

    basicMove.targetMove(robotData, (10,10), True)


    robotData[com.label.CLAMP.value] = 0
    robotData[com.label.HOOKS.value] = 0
    
    #time.sleep(0.1)


    basicMove.targetMove(robotData, (24,24))
    
    #time.sleep(0.1)  
