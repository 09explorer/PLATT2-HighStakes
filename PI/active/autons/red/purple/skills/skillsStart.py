import time
import autons.red.purple.skills.blueSide
import autons.red.purple.skills.wallStake
import autons.red.purple.skills.blueGoal
import communication as com
import functions.basicMove as basicMove
import autons.red.purple.skills.redSide
import functions.vision as vision

def skillsStart(robotData):

    startTime = time.time()

    cam = vision.vision()

    robotData[com.label.HEADINGOFFSET.value] = 90
    robotData[com.label.XPOSOFFSET.value] = 48
    robotData[com.label.YPOSOFFSET.value] = 18
    robotData[com.label.COLORSORT.value] = 2
    robotData[com.label.INTAKE.value] = 100
    robotData[com.label.WALLSTAKE.value] = 1
    robotData[com.label.INTAKEPISTON.value] = 1
    
    autons.red.purple.skills.redSide.redSide(robotData)
    autons.red.purple.skills.wallStake.wallStake(robotData, cam)
    autons.red.purple.skills.blueSide.blueSide(robotData)
    autons.red.purple.skills.blueGoal.blueGoal(robotData)


    endTime = time.time()
    print(endTime - startTime)
    time.sleep(1)


    #pass