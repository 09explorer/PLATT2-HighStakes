import time
from subsystems.label import label
from functions import basicMove
from subsystems.indicator import status
from subsystems.label import position
from functions.vision import vision
from functions.vision import color


def start(robotData):
    
    startTime = time.time()
    robotData[label.COLORSORT.value] = 2


    #basicMove.toPoint(robotData, (48,46), reverse=True, lookAhead=6)
    robotData[label.WALLSTAKE.value] = position.SCORELOW.value
    
    basicMove.toHeading(robotData, 220)

    basicMove.toPoint(robotData, (68,63), reverse=True, lookAhead=9)
    
    robotData[label.LEFTVEL.value] = 0
    robotData[label.RIGHTVEL.value] = 0
    time.sleep(0.25)
    robotData[label.CLAMP.value] = 1
    robotData[label.INTAKE.value] = 100
    robotData[label.INTAKEPISTON.value] = 1
    

    basicMove.toPoint(robotData, (30, 48), duration=5)
    robotData[label.HOOKS.value] = 100

    time.sleep(0.5)

    basicMove.toHeading(robotData, 270)
    
    robotData[label.INTAKEPISTON.value] = 0

    time.sleep(0.5)
    

    basicMove.toPoint(robotData, (24, 12), linVel=30, duration=5)
    
    basicMove.toHeading(robotData, 200)

    robotData[label.INTAKEPISTON.value] = 1

    basicMove.toPoint(robotData, (8, 8), linVel=25, duration=1)
    time.sleep(0.5)

    

    basicMove.toPoint(robotData, (24, 12), reverse=True, duration=1)

    basicMove.toHeading(robotData, 200)
    robotData[label.INTAKEPISTON.value] = 0
    time.sleep(0.5)

    basicMove.toPoint(robotData, (8, 8), linVel=25, duration=2)
    time.sleep(0.5)

    basicMove.toPoint(robotData, (36, 36), reverse=True, duration=1)

    basicMove.toHeading(robotData, 45)

    robotData[label.WALLSTAKE.value] = position.SCORE2.value
   
    basicMove.toPoint(robotData, (50, 48), duration=2)
    
    robotData[label.WALLSTAKE.value] = position.SCORELOW.value
    
    print(time.time()-startTime, flush=True)
    
    robotData[label.STATUSLIGHT.value] = status.FINNISHED.value
    
    pass