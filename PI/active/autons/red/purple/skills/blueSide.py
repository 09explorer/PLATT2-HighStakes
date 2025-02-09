import time
import communication as com
from functions import basicMove

def blueSide(robotData):

    
    basicMove.turnToHeading(robotData, 245)
 
    basicMove.targetMove(robotData, (50,98), True)
    
    robotData[com.label.CLAMP.value] = 1
    time.sleep(0.5)

    robotData[com.label.HOOKS.value] = 100

    basicMove.turnToHeading(robotData, 180)




    basicMove.targetMove(robotData, (26,96))



    basicMove.turnToHeading(robotData, 90)



    basicMove.targetMove(robotData, (24,117))



    basicMove.turnToHeading(robotData, 135)

    robotData[com.label.INTAKEPISTON.value] = 0


    basicMove.targetMove(robotData, (10, 142-10))
    robotData[com.label.INTAKEPISTON.value] = 1
    
    time.sleep(0.5)


    basicMove.targetMove(robotData, (24, 118), True)
    
    time.sleep(0.5)

    basicMove.targetMove(robotData, (10, 142 - 10))

    time.sleep(0.5)

    basicMove.targetMove(robotData, (24, 118), True)

    time.sleep(0.5)

    basicMove.relitiveTurn(robotData, 180)

    basicMove.targetMove(robotData, (10, 142-10), True)

    robotData[com.label.HOOKS.value] = 0
    robotData[com.label.CLAMP.value] = 0

    basicMove.targetMove(robotData, (24, 118))

