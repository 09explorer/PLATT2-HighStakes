import time
import qwiic_otos # type: ignore
from subsystems.label import label
from subsystems.indicator import status

def odom(robotData):
    
    while robotData[label.ALLIANCE.value] == 0:
        time.sleep(0.001)

    odom = qwiic_otos.QwiicOTOS()
    odom.begin()
    odom.calibrateImu()
    odom.setLinearScalar(1.0)
    odom.setAngularScalar(1.0)
    
    if robotData[label.ALLIANCE.value] == 1:
        if robotData[label.NAME.value] == 2:
            offset = qwiic_otos.Pose2D(0, 0, 180)
            startingPosition = qwiic_otos.Pose2D(0, 0, 0)
            startingPosition = qwiic_otos.Pose2D(93, 22, 249)
     
    odom.resetTracking()
    odom.setOffset(offset)
    odom.setPosition(startingPosition)

    robotData[label.STATUSLIGHT.value] = status.STANDBY.value

    while True:

        cPos = odom.getPosition()
         
        heading = cPos.h % 360
        
        if heading < 0:
            heading = heading + 360

        robotData[label.HEADING.value] =  heading
        
        robotData[label.XPOS.value]    =  cPos.x          
        robotData[label.YPOS.value]    =  cPos.y   
        time.sleep(0.001)
