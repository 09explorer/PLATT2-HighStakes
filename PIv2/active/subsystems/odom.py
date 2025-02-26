import time
import qwiic_otos # type: ignore
from subsystems.label import label

def odom(robotData):

    odom = qwiic_otos.QwiicOTOS()
    odom.begin()
    odom.calibrateImu()
    odom.setLinearScalar(1.0)
    odom.setAngularScalar(1.0)
    odom.resetTracking()
    offset = qwiic_otos.Pose2D(0, 0, 90)
    odom.setOffset(offset)

    while True:

        cPos = odom.getPosition()
         
        heading = cPos.h % 360
        
        if heading < 0:
            heading = heading + 360

        robotData[label.HEADING.value] =  heading + robotData[label.HEADINGOFFSET.value] 
        
        robotData[label.XPOS.value]    =  cPos.x  + robotData[label.XPOSOFFSET.value]          
        robotData[label.YPOS.value]    =  cPos.y  + robotData[label.YPOSOFFSET.value]   

        time.sleep(0.005)