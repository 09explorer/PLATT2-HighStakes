from subsystems.label import label
from functions import basicMove
from subsystems.indicator import status


def start(robotData):

    robotData[label.HEADINGOFFSET.value] = 90
    
    basicMove.toPoint(robotData, (0,20))

    robotData[label.STATUSLIGHT.value] = status.FINNISHED.value
    
    pass