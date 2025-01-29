import time
import communication as com
import functions.basicMove

def skillsStart(robotData):
    robotData[com.label.INTAKE.value] = 100
    functions.basicMove.targetMove(robotData, (48, 49), False, linVel=60)
    time.sleep(1)
    functions.basicMove.turnToHeading(robotData, 0)
    time.sleep(1)
    functions.basicMove.targetMove(robotData, (26, 48), True, linVel=40)
    robotData[com.label.CLAMP.value] = 1
    time.sleep(1)
    functions.basicMove.turnToHeading(robotData, 270)
    time.sleep(1)
    functions.basicMove.targetMove(robotData, (24, 25), False, linVel=40)
    time.sleep(1)
    functions.basicMove.targetMove(robotData, (7, 7), False, linVel=40)
    time.sleep(1)
    functions.basicMove.targetMove(robotData, (24, 24), True, linVel=20)
    time.sleep(1)
    functions.basicMove.turnToHeading(robotData, 45)
    time.sleep(1)
    functions.basicMove.targetMove(robotData, (7, 7), True, linVel=20)
    time.sleep(1)
    robotData[com.label.CLAMP.value] = 0
    time.sleep(1)
    pass