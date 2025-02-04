import time
import communication as com
from functions import basicMove

def blueGoal(robotData):

    basicMove.targetMove(robotData, (48, 96))

    

    basicMove.turnToHeading(robotData, 225)

   

    basicMove.targetMove(robotData, (73, 120), True)

    robotData[com.label.CLAMP.value] = 1

    basicMove.turnToHeading(robotData, 180)

    robotData[com.label.HOOKS.value] = 100

    basicMove.targetMove(robotData, (48, 120))

    basicMove.turnToHeading(robotData, 45)

    robotData[com.label.HOOKS.value] = 0
    robotData[com.label.WALLSTAKE.value] = 3 # may need to move

    basicMove.targetMove(robotData, (72, 128)) 
    
    
    
    basicMove.turnToHeading(robotData, 90)

    basicMove.targetMove(robotData, (72, 122), True)

    time.sleep(2)

    robotData[com.label.WALLSTAKE.value] = 5

    time.sleep(3)




    


