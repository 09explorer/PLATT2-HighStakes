import time
from subsystems.label import label
from functions import basicMove
from subsystems.indicator import status
from subsystems.label import position


def start(robotData):
    
    startTime = time.time()

    basicMove.toPoint(robotData, (30,42), linVel=100, kpTurn=0.8, reverse=True, lookAhead=10)
    
    basicMove.toPoint(robotData, (26,72), linVel=100, kpTurn=0.2, reverse=True, lookAhead=10)
    
    robotData[label.LEFTVEL.value] = 0
    robotData[label.RIGHTVEL.value] = 0
    time.sleep(0.25)
    robotData[label.CLAMP.value] = 1
    robotData[label.WALLSTAKE.value] = position.SCORE.value
    

    #basicMove.toPoint(robotData, (36,36), linVel=30, duration=2)
#
    #robotData[label.CLAMP.value] = 0 
#
    #basicMove.toPoint(robotData, (36,48), reverse=True, linVel=20, duration=2, lookAhead=5)
#
    #robotData[label.CLAMP.value] = 1
    #
    #print(time.time()-startTime, flush=True)
    #
    #robotData[label.STATUSLIGHT.value] = status.FINNISHED.value
    
    pass