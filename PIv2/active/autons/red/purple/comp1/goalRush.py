from functions import basicMove
from subsystems.label import label 
from subsystems.indicator import status
def goalRush(robotData):
    
    basicMove.toPoint(robotData, (120,57), reverse=True,linVel=55)
    #grab goal
    basicMove.toPoint(robotData, (100,40), reverse=False, linVel=55, duration=1)
    #drop goal
    basicMove.toHeading(robotData, (225), 1.5)
    basicMove.toPoint(robotData, (74,30),linVel=30, reverse=True)
    basicMove.toHeading(robotData, (90), 1) #turning sucks
    basicMove.toPoint(robotData, (74,20),linVel=30, reverse=False)
    basicMove.toHeading(robotData, (180), 1) #turning sucks
    basicMove.toPoint(robotData, (120,21),linVel=55, reverse=False)

    #intake on
    #wall stake score alliance


    robotData[label.STATUSLIGHT.value]= status.FINNISHED.value