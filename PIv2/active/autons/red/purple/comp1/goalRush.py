import time
from functions import basicMove
from subsystems.label import label 
from subsystems.indicator import status
from subsystems.label import position

def goalRush(robotData):
    
    robotData[label.WALLSTAKE.value] = position.LOAD.value
    robotData[label.COLORSORT.value] = 2
    
    
    basicMove.toPoint(robotData, (110,60), reverse=True,linVel=100, lookAhead=6, kpTurn=1, duration=1.5)
    
    robotData[label.CLAMP.value] = 1
    robotData[label.HOOKS.value] = 100
    time.sleep(0.25)
    
    basicMove.toPoint(robotData, (96,48), kpTurn  = 1, duration=1)

    
    robotData[label.CLAMP.value] = 0

    basicMove.toHeading(robotData, (45), 1.5)
    
    basicMove.toPoint(robotData, (72,24),linVel=30, reverse=True)
    
    robotData[label.CLAMP.value] = 1 
    robotData[label.INTAKE.value] = 100
    

    basicMove.toHeading(robotData, (275), kplin=0.35)

    basicMove.toPoint(robotData, (72,17), lookAhead=2, linVel=20, kpTurn=0.4)

    basicMove.toHeading(robotData, (275))

    robotData[label.WALLSTAKE.value] = position.SCORELOW2.value

    time.sleep(1)

    robotData[label.WALLSTAKE.value] = position.SCORE.value

    basicMove.toPoint(robotData, (72,24),linVel=30, reverse=True)

    basicMove.toHeading(robotData, (0))

    basicMove.toPoint(robotData, (118,24))

    basicMove.toHeading(robotData, (90), kplin=0.35)

    robotData[label.INTAKEPISTON.value] = 1

    basicMove.toPoint(robotData, (118, 48))

    basicMove.toHeading(robotData, 45)

    basicMove.toPoint(robotData, (127.5, 64.5), linVel=30)

    basicMove.toPoint(robotData, (130, 12), reverse=True)
   
    basicMove.toHeading(robotData, 300)

    basicMove.toPoint(robotData, (135, 6), linVel=20, kpTurn=1.5, duration=2)

    basicMove.toPoint(robotData, (130, 12), linVel=20, kpTurn=1.5, duration=2, reverse=True)

    basicMove.toHeading(robotData, 300)

    basicMove.toPoint(robotData, (135, 6), linVel=20, kpTurn=1.5, duration=2)

    basicMove.toPoint(robotData, (120, 22), linVel=20, kpTurn=1.5, duration=2, reverse=True)

    basicMove.toHeading(robotData, 135)

    basicMove.toPoint(robotData, (72, 48), duration=2.5)


    










   