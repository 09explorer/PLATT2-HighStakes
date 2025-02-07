import time
import communication as com
from functions import basicMove
from functions import vision
def blueGoal(robotData, cam):

    basicMove.targetMove(robotData, (48, 96))

    

    basicMove.turnToHeading(robotData, 225)

   

    basicMove.targetMove(robotData, (70, 118), True)

    robotData[com.label.CLAMP.value] = 1
    time.sleep(0.5)

    basicMove.turnToHeading(robotData, 180)

    robotData[com.label.HOOKS.value] = 100
   
    basicMove.targetMove(robotData, (50, 120))

    time.sleep(1)


    basicMove.turnToHeading(robotData, 45)

    

    basicMove.targetMove(robotData, (72, 128)) 
    
    basicMove.targetMove(robotData, (48,96), True)
    robotData[com.label.WALLSTAKE.value] = 6
    basicMove.turnToHeading(robotData, 315)
    
    basicMove.targetMove(robotData, (95,35))

    basicMove.relitiveTurn(robotData, 180)

    cam.chase(robotData, vision.color.RED)




    


