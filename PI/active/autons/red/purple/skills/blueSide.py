import time
import communication as com
from functions import basicMove

def blueSide(robotData):

    
    basicMove.turnToHeading(robotData, 245)
 
    basicMove.targetMove(robotData, (48,94), True)
    
    robotData[com.label.CLAMP.value] = 1

    time.sleep(0.5)
    robotData[com.label.HOOKS.value] = 100

    basicMove.turnToHeading(robotData, 180)




    basicMove.targetMove(robotData, (24,96))



    basicMove.turnToHeading(robotData, 90)



    basicMove.targetMove(robotData, (24,120))



    basicMove.turnToHeading(robotData, 135)

    robotData[com.label.INTAKEPISTON.value] = 0


    basicMove.targetMove(robotData, (12, 144-12))
    robotData[com.label.INTAKEPISTON.value] = 1
    
    time.sleep(1)

    basicMove.targetMove(robotData, (24, 120), True)
    
    time.sleep(1)

    basicMove.targetMove(robotData, (12, 144 - 12))
 
    basicMove.targetMove(robotData, (24, 120), True)

    time.sleep(1)

    basicMove.relitiveTurn(robotData, 180)

    basicMove.targetMove(robotData, (12, 144-12), True)

    robotData[com.label.HOOKS.value] = 0
    robotData[com.label.CLAMP.value] = 0

    basicMove.targetMove(robotData, (24, 120))

