import time
import serial
from subsystems.label import label
from subsystems.indicator import status

readPort  = 0
writePort = 0

def getSubString(rawRead, prefix):
    
    index = rawRead.find(prefix)
    endIndex = rawRead.find(";", index+1)

    return float(rawRead[index+1:endIndex])


def addToWriteString(writeString, prefix, data):

    newString = writeString + prefix + str(data) + ';'

    return newString


def connect(robotData):
   

    while True:
        try:
            readName = '/dev/ttyACM0'
            writeName = '/dev/ttyACM1'

            readPort  = serial.Serial(readName, timeout=0)
            writePort = serial.Serial(writeName, timeout=0)

            robotData[label.STATUSLIGHT.value] = status.CONNECTED.value

            print("connected", flush=True)

        except:
            time.sleep(0.1)
            robotData[label.STATUSLIGHT.value] = status.DISCONNECTED.value
        
        else:
            return readPort, writePort
            
        
def recvData(robotData):
    
    global readPort
    global writePort

    rawRead = ''
    while True:
        try:
            if readPort.in_waiting:
                rawRead = rawRead + readPort.readall().decode()
           
                if '/' in rawRead:
                    return rawRead
        except:
            _ = connect(robotData) 
            readPort  = _[0]
            writePort = _[1]
            return recvData(robotData)
        
        
def writeData(robotData, writeString):

    global readPort
    global writePort

    try:
        writePort.write(writeString.encode())
    
    except:
        _ = connect(robotData) 
        readPort  = _[0]
        writePort = _[1]
        writeData(robotData, writeString)

            
def piCom(robotData):
    
    global readPort
    global writePort

    _ = connect(robotData) 
    readPort  = _[0]
    writePort = _[1]

    while True:
        
        rawRead = recvData(robotData)
       
        robotData[label.RUN.value]      = getSubString(rawRead, 'x')
        robotData[label.NAME.value]     = getSubString(rawRead, 'n')
        robotData[label.AUTON.value]    = getSubString(rawRead, 'u')
        robotData[label.ALLIANCE.value] = getSubString(rawRead, 'a')

        writeString = ''
        writeString = addToWriteString(writeString, 'r', robotData[label.RIGHTVEL.value])
        writeString = addToWriteString(writeString, 'l', robotData[label.LEFTVEL.value])
        writeString = addToWriteString(writeString, 'c', robotData[label.CLAMP.value])
        writeString = addToWriteString(writeString, 'w', robotData[label.WALLSTAKE.value])
        writeString = addToWriteString(writeString, 's', robotData[label.COLORSORT.value])
        writeString = addToWriteString(writeString, 'i', robotData[label.INTAKE.value])
        writeString = addToWriteString(writeString, 'o', robotData[label.HOOKS.value])
        writeString = addToWriteString(writeString, 'p', robotData[label.INTAKEPISTON.value])
        writeString = writeString + '/'

        time.sleep(0.001)

        writeData(robotData, writeString)

           






    