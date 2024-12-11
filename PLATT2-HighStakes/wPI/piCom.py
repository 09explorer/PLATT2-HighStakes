import serial
import time
from enum import Enum

class data(Enum):
    
    FLAG = 1
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

#picks apart given string to find the data marked by a given prefix
def getSubString(rawRead, prefix):
    
    index = rawRead.find(prefix)
    endIndex = rawRead.find(";", index+1)

    return float(rawRead[index+2:endIndex])

def addToWriteString(robotData, writeString, prefix, enum):

    writeString = prefix + ':' + str(robotData[enum]) + ';'

    return writeString

#function to exchange data with vex brain using serial ports
def startLink(robotData):
    
    #open serial ports on PI 
    readPort  = serial.Serial('/dev/ttyACM0', timeout=0)
    writePort = serial.Serial('/dev/ttyACM1')
     
    while True:

        #capture incoming serial data until the stop bit is read 
        rawRead = ''
        while True:

            if readPort.in_waiting:
                rawRead = rawRead + readPort.readall().decode()
                if '/' in rawRead:
                    break
        
        #get and assign data to the shared buffer 
        robotData[data.FLAG.value] = getSubString(rawRead, 'f') #status
        robotData[data.XPOS.value] = getSubString(rawRead, 'x') #odomX
        robotData[data.YPOS.value] = getSubString(rawRead, 'y') #odomY
        robotData[data.HEADING.value] = getSubString(rawRead, 'h') #odomH
        
        #get data from shared buffer to write 
        writeString = ''
        writeString = addToWriteString(robotData, writeString, 'r', data.RIGHTVEL.value)
        writeString = addToWriteString(robotData, writeString, 'l', data.LEFTVEL.value)
        writeString = addToWriteString(robotData, writeString, 'c', data.CLAMP.value)
        writeString = addToWriteString(robotData, writeString, 'w', data.WALLSTAKE.value)
        writeString = addToWriteString(robotData, writeString, 's', data.COLORSORT.value)
        writeString = addToWriteString(robotData, writeString, 'i', data.INTAKE.value)
        writeString = addToWriteString(robotData, writeString, 'o', data.HOOKS.value)
        

        
        #wait needed for stability 
        time.sleep(0.001)
        
        #create write string 
        writeString = writeString + '/'
        
        #send write string 
        writePort.write(writeString.encode())