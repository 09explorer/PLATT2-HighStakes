from cmath import atan, sqrt, pi
from math import atan2, copysign
import time
from subsystems.label import label
import multiprocessing as mp


def timeout(robotData, duration):
    
    startTime = time.time()

    while time.time() < startTime + duration:
        time.sleep(0.01)
    
    if duration == 0:
        while True:
            time.sleep(1)

    robotData[label.LEFTVEL.value] = 0
    robotData[label.RIGHTVEL.value] = 0

def toPointMath(robotData, target, reverse):

    offset = sqrt(((robotData[label.XPOS.value]-target[0])**2)+((robotData[label.YPOS.value]-target[1])**2))
    startOffset = offset
    if reverse:
        scale = -1
    else:
        scale = 1 
    
    if offset <= 10:
        
        while offset >= 1:
              
            linVel = (4/-pow(startOffset, 1.75))(offset-startOffset)(0.5*offset)
                      
            absTargetAngle = atan2(target[1] - robotData[label.YPOS.value], target[0] - robotData[label.XPOS.value]) * (180/pi)

            if reverse:
                absTargetAngle += 180
            
            if absTargetAngle < 0:
                absTargetAngle += 360
            
            turnError = absTargetAngle - robotData[label.HEADING.value]

            if turnError > 180 or turnError < -180:

                turnError = -1 * copysign(1, turnError) * (360 - abs(turnError))

            turnvel = turnError*0.4

            robotData[label.LEFTVEL.value]  = scale*linVel + turnvel
            robotData[label.RIGHTVEL.value] = scale*linVel - turnvel

            offset = sqrt(((robotData[label.XPOS.value]-target[0])**2)+((robotData[label.YPOS.value]-target[1])**2))
       
    else:
        
        while offset >=1:

            if offset < startOffset/2:

                linVel = 1.15*((atan(0.5*(offset)))/0.5*pi)

            else:

                linVel = 1.15*((-atan(0.5*(offset-startOffset)))/0.5*pi)

            absTargetAngle = atan2(target[1] - robotData[label.YPOS.value], target[0] - robotData[label.XPOS.value]) * (180/pi)

            if reverse:
                absTargetAngle += 180
            
            if absTargetAngle < 0:
                absTargetAngle += 360
            
            turnError = absTargetAngle - robotData[label.HEADING.value]

            if turnError > 180 or turnError < -180:

                turnError = -1 * copysign(1, turnError) * (360 - abs(turnError))

            turnvel = turnError*0.4

            robotData[label.LEFTVEL.value]  = linVel + turnvel
            robotData[label.RIGHTVEL.value] = linVel - turnvel

            offset = sqrt(((robotData[label.XPOS.value]-target[0])**2)+((robotData[label.YPOS.value]-target[1])**2))

    robotData[label.LEFTVEL.value]  = 0
    robotData[label.RIGHTVEL.value] = 0


def toPoint(robotData, target, reverse, duration = 0):

    math = mp.Process(target=toPointMath, args=(robotData,target,reverse,))
    math.daemon = True
    math.start()

    timeOut = mp.Process(target=timeout, args=(robotData,duration,))
    timeOut.daemon = True
    timeOut.start()

    while math.is_alive() and timeOut.is_alive():
        time.sleep(0.01)
    
    if math.is_alive():
        math.terminate()
    
    if timeOut.is_alive():
        timeOut.terminate()
