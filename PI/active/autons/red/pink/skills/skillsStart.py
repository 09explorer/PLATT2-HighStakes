import autons.red.pink.skills.wallStake
import communication as com
import autons.red.pink.skills.redside
import autons.red.pink.skills.blueSide
import functions.vision as vision
import time

def skillsStart(robotData):
    
    startTime = time.time()

    robotData[com.label.HEADINGOFFSET.value] = 90
    robotData[com.label.XPOSOFFSET.value] = 72.5
    robotData[com.label.YPOSOFFSET.value] = 12
    robotData[com.label.COLORSORT.value] = 2
    robotData[com.label.INTAKE.value] = 100
    robotData[com.label.WALLSTAKE.value] = 3
    robotData[com.label.INTAKEPISTON.value] = 1
    robotData[com.label.HOOKS.value] = 100
    

    autons.red.pink.skills.redside.redSide(robotData)
    autons.red.pink.skills.wallStake.wallStake(robotData)
    autons.red.pink.skills.blueSide.blueSide(robotData)

    endTime = time.time()
    print(endTime - startTime)
    time.sleep(1)

    
    pass