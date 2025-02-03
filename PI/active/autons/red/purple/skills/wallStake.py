    
import time
import communication as com
from functions import basicMove


def wallStake(robotData):

    robotData[com.label.HOOKS.value] = 100

    robotData[com.label.WALLSTAKE.value] = 3

    basicMove.targetMove(robotData, (15, 48), turnVel=0.6)

    basicMove.targetMove(robotData, (15, 66))

    time.sleep(1)
    robotData[com.label.INTAKEPISTON.value] = 0
    basicMove.turnToHeading(robotData, 180)



    robotData[com.label.WALLSTAKE.value] = 1
    

    time.sleep(1.5)
    robotData[com.label.HOOKS.value] = 0
    robotData[com.label.WALLSTAKE.value] = 4

    basicMove.turnToHeading(robotData, 0)

    robotData[com.label.INTAKEPISTON.value] = 1

    basicMove.targetMove(robotData, (36, 78))













