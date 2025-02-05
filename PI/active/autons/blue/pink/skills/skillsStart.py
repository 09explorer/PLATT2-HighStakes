import time
import functions.basicMove as basicMove
import communication as com

def skillsStart(robotData):

    robotData[com.label.HEADINGOFFSET.value] = 90
    robotData[com.label.XPOSOFFSET.value] = 48
    robotData[com.label.YPOSOFFSET.value] = 18


    basicMove.turnToHeading(robotData, 0)

    time.sleep(2)
    print(robotData[com.label.HEADING.value], flush=True)

    pass