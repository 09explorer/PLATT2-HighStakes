import time
import serial
from label import label
from indicator import status

def getSubString(rawRead, prefix):
    
    index = rawRead.find(prefix)
    endIndex = rawRead.find(";", index+1)

    return float(rawRead[index+1:endIndex])

def addToWriteString(writeString, prefix, data):

    newString = writeString + prefix + str(data) + ';'

    return newString

def piCom(robotData):

    robotData[label.STATUSLIGHT.value] = status.LINKWAIT.value

    while True:
        try:
            readName = '/dev/ttyACM0'
            writeName = '/dev/ttyACM1'

            readPort  = serial.Serial(readName, timeout=0)
            writePort = serial.Serial(writeName, timeout=0)

        except:
            time.sleep(1)
            print("link fail: waiting for link", flush=True)
        
        else:
            print("link established", flush=True)
            break

    robotData[label.STATUSLIGHT.value] = status.STANDBY.value

    while True:
        
        rawRead = ''

        while True:
    
            if readPort.in_waiting:
                rawRead = rawRead + readPort.readall().decode()
                if '/' in rawRead:
                    break

        robotData[label.RESET.value]    = getSubString(rawRead, 'x')
        robotData[label.NAME.value]     = getSubString(rawRead, 'n')
        robotData[label.AUTON.value]    = getSubString(rawRead, 'u')
        robotData[label.ALLIANCE.value] = getSubString(rawRead, 'a')

        writeString = ''
        writeString = addToWriteString(robotData, writeString, 'r', label.RIGHTVEL.value)
        writeString = addToWriteString(robotData, writeString, 'l', label.LEFTVEL.value)
        writeString = addToWriteString(robotData, writeString, 'c', label.CLAMP.value)
        writeString = addToWriteString(robotData, writeString, 'w', label.WALLSTAKE.value)
        writeString = addToWriteString(robotData, writeString, 's', label.COLORSORT.value)
        writeString = addToWriteString(robotData, writeString, 'i', label.INTAKE.value)
        writeString = addToWriteString(robotData, writeString, 'o', label.HOOKS.value)
        writeString = addToWriteString(robotData, writeString, 'p', label.INTAKEPISTON.value)
        writeString = writeString + '/'

        time.sleep(0.001)
        writePort.write(writeString.encode())




    