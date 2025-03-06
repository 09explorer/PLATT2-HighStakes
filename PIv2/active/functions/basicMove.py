from math import atan2, copysign, sqrt, pi, atan
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

def toPointMath(robotData, target, reverse, linVel, lookAhead, kpTurn):
    
    offset = sqrt(((robotData[label.XPOS.value]-target[0])**2)+((robotData[label.YPOS.value]-target[1])**2))
    startOffset = offset
    
    if reverse:
        scale = -1
    else:
        scale = 1 
    
    turnError = 0
    while offset>lookAhead:
            
        #linVel = 1.15*((atan((0.2)*(offset-1)))/(0.5*pi))*linVel
    

        if linVel > 100:
            linVel = 100

        absTargetAngle = atan2(target[1] - robotData[label.YPOS.value], target[0] - robotData[label.XPOS.value]) * (180/pi)

        if reverse:
            absTargetAngle += 180
            
        if absTargetAngle < 0:
            absTargetAngle += 360
            
        turnError = absTargetAngle - robotData[label.HEADING.value]

        if turnError > 180 or turnError < -180:

            turnError = -1 * copysign(1, turnError) * (360 - abs(turnError))

        turnvel = turnError*kpTurn
                    
        leftvel = scale*linVel - turnvel
        rightvel = scale*linVel + turnvel

        if abs(leftvel)>100:
            if leftvel>0:
                rightvel = rightvel - (leftvel - 100)
            else:
                rightvel = rightvel - (leftvel + 100)

            leftvel = copysign(100, leftvel)
            
        if abs(rightvel)>100:
            if rightvel > 0:
                leftvel = leftvel - (rightvel - 100)
            else:
                leftvel = leftvel - (rightvel + 100)

            rightvel = copysign(100, rightvel)

        #print(leftvel, flush=True)
        robotData[label.LEFTVEL.value]  = leftvel
        robotData[label.RIGHTVEL.value] = rightvel

        offset = sqrt(((robotData[label.XPOS.value]-target[0])**2)+((robotData[label.YPOS.value]-target[1])**2))

        time.sleep(0.005)



def toPoint(robotData, target, linVel = 55, reverse = False, duration = 0, lookAhead = 3, kpTurn = 0.5):

    math = mp.Process(target=toPointMath, args=(robotData,target,reverse,linVel,lookAhead, kpTurn))
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
    

def toHeadingMath(robotData, target, kplin):
    
    turnError = 180
    avg = [180] * 30
    
    while abs(turnError) > 1.5 or sum(avg)/len(avg) > 1.5:

        turnError = target - robotData[label.HEADING.value]
    
        if turnError > 180 or turnError < -180:

            turnError = -1 * copysign(1, turnError) * (360 - abs(turnError))

        turnVel = turnError*kplin
        
        robotData[label.LEFTVEL.value] =   -turnVel
        robotData[label.RIGHTVEL.value] =  +turnVel
 
        avg.pop(0)
        avg.append(abs(turnError))
        
        time.sleep(0.01)
         
    robotData [label.LEFTVEL.value] = 0
    robotData [label.RIGHTVEL.value] = 0



def toHeading(robotData, target, duration = 0, kplin=0.5):

    math = mp.Process(target=toHeadingMath, args=(robotData,target, kplin))
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

    robotData [label.LEFTVEL.value] = 0
    robotData [label.RIGHTVEL.value] = 0




