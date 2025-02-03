import time
import communication as com
from functions import basicMove

def blueSide(robotData):

    
    basicMove.turnToHeading(robotData, 225)

    time.sleep(0.1)
    
    basicMove.targetMove(robotData, (48,96), True)

    robotData[com.label.HOOKS.value] = 100

    time.sleep(0.1)

    
    robotData[com.label.CLAMP.value] = 1

    time.sleep(1)
    robotData[com.label.HOOKS.value] = 100

    basicMove.turnToHeading(robotData, 180)

    time.sleep(0.1)


    basicMove.targetMove(robotData, (24,96))

    time.sleep(0.1)

    basicMove.turnToHeading(robotData, 90)

    time.sleep(0.1)

    basicMove.targetMove(robotData, (24,120))

    time.sleep(0.1)

    basicMove.turnToHeading(robotData, 135)

    robotData[com.label.INTAKEPISTON.value] = 0
    time.sleep(0.1)

    basicMove.targetMove(robotData, (10,136))
    robotData[com.label.INTAKEPISTON.value] = 1
    time.sleep(1)

    basicMove.targetMove(robotData, (24, 120), True)
    time.sleep(0.1)

    basicMove.targetMove(robotData, (10, 136))
    time.sleep(0.1)
    basicMove.targetMove(robotData, (24, 120), True)

    time.sleep(0.1)
    basicMove.relitiveTurn(robotData, 135)

    basicMove.targetMove(robotData, (10, 136), True)

    robotData[com.label.HOOKS.value] = 100
    robotData[com.label.CLAMP.value] = 0

