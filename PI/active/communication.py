import serial
import platform
import time
from enum import Enum

class label(Enum):
    
    NAME = 1
    RIGHTVEL = 2
    LEFTVEL = 3
    CLAMP = 4
    WALLSTAKE= 5
    COLORSORT = 6
    HEADING = 7
    XPOS = 8
    YPOS = 9 
    INTAKE = 10
    HOOKS = 11   
    AUTON = 12
    ALLIANCE = 13
    FLAG = 14

def getSubString(rawRead, prefix):
    
    index = rawRead.find(prefix)
    endIndex = rawRead.find(";", index+1)

    return float(rawRead[index+2:endIndex])

def addToWriteString(robotData, writeString, prefix, data):

    newString = writeString + prefix + ':' + str(robotData[data]) + ';'

    return newString


def startLink(robotData):
    
    #open serial ports on PI 

    #print("hello", flush= True)

    readName = '/dev/ttyACM0'
    writeName = '/dev/ttyACM1'

    readPort  = serial.Serial(readName, timeout=0)
    writePort = serial.Serial(writeName)

    rawRead = ''

    while True:
    
        if readPort.in_waiting:
            rawRead = rawRead + readPort.readall().decode()
            if '/' in rawRead:
                break
    #print(rawRead,flush=True)
    robotData[label.NAME.value]     = getSubString(rawRead, 'n') #odomX
    robotData[label.AUTON.value]    = getSubString(rawRead, 'u') #odomY
    robotData[label.ALLIANCE.value] = getSubString(rawRead, 'a') #odomH

     
    #print("hello", flush= True)

    while True:

        #capture incoming serial data until the stop bit is read 
        rawRead = ''
        while True:

            if readPort.in_waiting:
                rawRead = rawRead + readPort.readall().decode()
                if '/' in rawRead:
                    break
        
        #print(rawRead,flush=True)
        
        #get and assign data to the shared buffer 
        robotData[label.FLAG.value]    = getSubString(rawRead, 'f') #status
        #print(robotData[label.FLAG.value],flush=True)
        robotData[label.HEADING.value] = getSubString(rawRead, 'h') #odomH
        robotData[label.XPOS.value]    = getSubString(rawRead, 'x') #odomX
        robotData[label.YPOS.value]    = getSubString(rawRead, 'y') #odomY
        
        
        #get data from shared buffer to write 
        writeString = ''
        writeString = addToWriteString(robotData, writeString, 'r', label.RIGHTVEL.value)
        writeString = addToWriteString(robotData, writeString, 'l', label.LEFTVEL.value)
        writeString = addToWriteString(robotData, writeString, 'c', label.CLAMP.value)
        writeString = addToWriteString(robotData, writeString, 'w', label.WALLSTAKE.value)
        writeString = addToWriteString(robotData, writeString, 's', label.COLORSORT.value)
        writeString = addToWriteString(robotData, writeString, 'i', label.INTAKE.value)
        writeString = addToWriteString(robotData, writeString, 'o', label.HOOKS.value)
    
        
        #wait needed for stability 
        time.sleep(0.0001)
        
        #create write string 
        writeString = writeString + '/'
        #print (writeString, flush=True)
        #print(writeString,flush=True)
        
        #send write string 
        writePort.write(writeString.encode())
    