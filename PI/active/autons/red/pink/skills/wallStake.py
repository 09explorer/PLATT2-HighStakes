import time
import communication as com
from functions import basicMove
import functions.vision as vision

def wallStake(robotData):

    
    # Hooks action remains the same
    robotData[com.label.HOOKS.value] = 100

    # Wall stake action remains the same
    robotData[com.label.WALLSTAKE.value] = 3

    # Mirror the first target move (15, 48) -> (129, 48)
    basicMove.targetMove(robotData, (130, 48), turnVel=0.6)

    # Mirror the second target move (15, 66) -> (129, 66)
    basicMove.targetMove(robotData, (130, 72))

    time.sleep(1)

    # Intake piston action remains the same
    robotData[com.label.INTAKEPISTON.value] = 0

    # Mirror the turn to heading 180 -> 180 (remains the same)
    basicMove.turnToHeading(robotData, 0)

    # Wall stake action remains the same
    robotData[com.label.WALLSTAKE.value] = 1

    time.sleep(0.5)

    # Hooks and wall stake actions remain the same
    robotData[com.label.HOOKS.value] = 0
    robotData[com.label.WALLSTAKE.value] = 4

    time.sleep(0.5)

    # Mirror the third target move (22, 66) -> (122, 66)
    basicMove.targetMove(robotData, (122, 72), True)

    # Mirror the turn to heading 0 -> 0 (remains the same)
    basicMove.turnToHeading(robotData, 135)

    # Hooks and intake piston actions remain the same
    robotData[com.label.HOOKS.value] = -50
    robotData[com.label.INTAKEPISTON.value] = 1

    time.sleep(1)
    robotData[com.label.HOOKS.value] = 0

    basicMove.targetMove(robotData, (144-33, 75))# jank needs fixing


    basicMove.turnToHeading(robotData, 0)
    basicMove.turnToHeading(robotData, 310)