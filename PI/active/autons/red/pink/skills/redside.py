from functions import basicMove
import communication as com
import time

def redSide(robotData):

    time.sleep(0.1)
    basicMove.targetMove(robotData, (77, 18))

    time.sleep(0.5)

    basicMove.turnToHeading(robotData, 270)

    robotData[com.label.WALLSTAKE.value] = 6

    time.sleep(2)

    robotData[com.label.HOOKS.value] = 0

    basicMove.targetMove(robotData, (72, 36), True)    


    basicMove.targetMove(robotData, (97, 47))

    robotData[com.label.WALLSTAKE.value] = 1

    basicMove.turnToHeading(robotData, 180)
#
#    # Mirror the second target move (26,45) -> (118,45)
    basicMove.targetMove(robotData, (120, 48), True, linVel=20)
#
#    # Clamp action remains the same
    robotData[com.label.CLAMP.value] = 1

    time.sleep(0.5)
    robotData[com.label.HOOKS.value] = 100 
#    # Turn to heading 270 remains the same
    basicMove.turnToHeading(robotData, 270)

#
#    # Hooks action remains the same
    
#
#    # Mirror the third target move (22,24) -> (122,24)
    basicMove.targetMove(robotData, (122, 24))
#    
    #time.sleep(0.1)
#   
#    # Mirror the turn to heading 225 -> 135
    basicMove.turnToHeading(robotData, 315)
#
#    #time.sleep(0.1)
#
#    # Mirror the fourth target move (8,8) -> (136,8)
    basicMove.targetMove(robotData, (136, 8))
#
#    #time.sleep(0.1)
#
#    # Mirror the fifth target move (18,18) -> (126,18)
    basicMove.targetMove(robotData, (126, 18), True)
#    
    time.sleep(1)
#
#    # Relative turn of 180 remains the same
    basicMove.relitiveTurn(robotData, 180)    
#
#    # Mirror the sixth target move (10,10) -> (134,10)
    basicMove.targetMove(robotData, (134, 10), True)
#
#    # Clamp and hooks actions remain the same
    robotData[com.label.CLAMP.value] = 0
    robotData[com.label.HOOKS.value] = 0
#    
#    #time.sleep(0.1)
#
#    # Mirror the seventh target move (24,24) -> (120,24)
    basicMove.targetMove(robotData, (120, 24))
#    
#    #time.sleep(0.1)