import time
import communication as com
from functions import basicMove

def blueSide(robotData):

    # Mirror the turn to heading 245 -> 115 (360 - 245)
    
    # Mirror the first target move (48, 94) -> (96, 94)
    basicMove.targetMove(robotData, (98, 94), True, linVel=20)
    time.sleep(0.5)
    # Clamp action remains the same
    robotData[com.label.CLAMP.value] = 1

    time.sleep(0.5)

    # Hooks action remains the same
    robotData[com.label.HOOKS.value] = 100

    # Mirror the turn to heading 180 -> 180 (remains the same)
    basicMove.turnToHeading(robotData, 0)

    # Mirror the second target move (24, 96) -> (120, 96)
    basicMove.targetMove(robotData, (120, 96))

    # Mirror the turn to heading 90 -> 270 (360 - 90)
    basicMove.turnToHeading(robotData, 90)

    # Mirror the third target move (24, 120) -> (120, 120)
    basicMove.targetMove(robotData, (120, 119))

    # Mirror the turn to heading 135 -> 225 (360 - 135)
    basicMove.turnToHeading(robotData, 45)

    # Intake piston action remains the same
    robotData[com.label.INTAKEPISTON.value] = 0
    robotData[com.label.HOOKS.value] = 0


    # Mirror the fourth target move (12, 132) -> (132, 132)
    basicMove.targetMove(robotData, (134, 134), turnVel=0.6)
    basicMove.turnToHeading(robotData, 45)

    # Intake piston action remains the same
    robotData[com.label.INTAKEPISTON.value] = 1
    robotData[com.label.HOOKS.value] = 100
    
    time.sleep(1)

    # Mirror the fifth target move (24, 120) -> (120, 120)
    basicMove.targetMove(robotData, (120, 120), True)
    basicMove.turnToHeading(robotData, 45)
    time.sleep(1)

    # Mirror the sixth target move (12, 132) -> (132, 132)
    basicMove.targetMove(robotData, (134, 134), turnVel=0.6)
    basicMove.turnToHeading(robotData, 45)
 
    # Mirror the seventh target move (24, 120) -> (120, 120)
    basicMove.targetMove(robotData, (120, 120), True)
    basicMove.turnToHeading(robotData, 45)
    time.sleep(1)

    # Relative turn of 180 remains the same
    basicMove.turnToHeading(robotData, 225)
    # basicMove.relitiveTurn(robotData, 180)

    # Mirror the eighth target move (12, 132) -> (132, 132)
    basicMove.targetMove(robotData, (133, 133), True)

    # Hooks and clamp actions remain the same
    
    robotData[com.label.CLAMP.value] = 0
    
    # Mirror the ninth target move (24, 120) -> (120, 120)
    basicMove.targetMove(robotData, (120, 120))
    robotData[com.label.WALLSTAKE.value] = 3

    basicMove.targetMove(robotData, (96, 120))

    basicMove.targetMove(robotData, (72, 120))

    basicMove.turnToHeading(robotData, 90)

    basicMove.targetMove(robotData, (72, 126.5))

    basicMove.turnToHeading(robotData, 90)

    robotData[com.label.WALLSTAKE.value] = 6