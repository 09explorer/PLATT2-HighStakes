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
    AUTON = 13
    ALLIANCE = 12

def getSubString(rawRead, prefix):
    
    index = rawRead.find(prefix)
    endIndex = rawRead.find(";", index+1)

    return float(rawRead[index+2:endIndex])

def addToWriteString(robotData, writeString, prefix, data):

    writeString = prefix + ':' + str(robotData[data]) + ';'

    return writeString


def holdForInit():
    
    if platform.system() == "Windows":
        portName = '' #need correct COM port for Brain Comuications
    else:
        portName = '/dev/ttyACM0'
    
    readPort  = serial.Serial(portName, timeout=0)

    rawRead = ''

    while True:
    
        if readPort.in_waiting:
            rawRead = rawRead + readPort.readall().decode()
            if '/' in rawRead:
                break
        time.sleep(0.01)
    
    name    = getSubString(rawRead, 'x') #odomX
    auton   = getSubString(rawRead, 'y') #odomY
    alliance = getSubString(rawRead, 'h') #odomH

    readPort.close()

    return name, auton, alliance

def startLink(robotData):
    
    #open serial ports on PI 
    if platform.system() == "Windows":
        readName = ''
        writeName = '' #need correct COM port for Brain Comuications
    else:
        readName = '/dev/ttyACM0'
        writeName = '/dev/ttyACM1'


    readPort  = serial.Serial(readName, timeout=0)
    writePort = serial.Serial(writeName)
     
    while True:

        #capture incoming serial data until the stop bit is read 
        rawRead = ''
        while True:

            if readPort.in_waiting:
                rawRead = rawRead + readPort.readall().decode()
                if '/' in rawRead:
                    break
        
        #get and assign data to the shared buffer 
        robotData[label.FLAG.value] = getSubString(rawRead, 'f') #status
        robotData[label.XPOS.value] = getSubString(rawRead, 'x') #odomX
        robotData[label.YPOS.value] = getSubString(rawRead, 'y') #odomY
        robotData[label.HEADING.value] = getSubString(rawRead, 'h') #odomH
        
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
        time.sleep(0.001)
        
        #create write string 
        writeString = writeString + '/'
        
        #send write string 
        writePort.write(writeString.encode())
    