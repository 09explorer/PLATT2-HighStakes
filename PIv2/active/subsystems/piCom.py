import time
import serial
from subsystems.label import label
from subsystems.indicator import status

def getSubString(rawRead, prefix):
    
    index = rawRead.find(prefix)
    endIndex = rawRead.find(";", index+1)

    return float(rawRead[index+1:endIndex])

def addToWriteString(writeString, prefix, data):

    newString = writeString + prefix + str(data) + ';'

    return newString

def piCom(robotData):

    robotData[label.STATUSLIGHT.value] = status.LINKWAIT.value
    iteration = 0
    while True:
        try:
            readName = '/dev/ttyACM0'
            writeName = '/dev/ttyACM1'

            readPort  = serial.Serial(readName, timeout=0)
            writePort = serial.Serial(writeName, timeout=0)

        except:
            time.sleep(1)
            if iteration == 0:
                print("link fail: waiting for link", flush=True)
            robotData[label.STATUSLIGHT.value] = status.LINKWAIT.value
            iteration = 1
        
        else:

            break

    robotData[label.STATUSLIGHT.value] = status.LINKESTABLISH.value
    iteration = 1

    while True:
        
        rawRead = ''

        while True:
            
            if iteration == 1:
                robotData[label.STATUSLIGHT.value] = status.LINKESTABLISH.value
            try:
                if readPort.in_waiting:
                    rawRead = rawRead + readPort.readall().decode()
               
                    if '/' in rawRead:
                        break
            except:
                del readPort
                readPort  = serial.Serial(readName, timeout=0)
                break


                    
        robotData[label.RESET.value]    = getSubString(rawRead, 'x')
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
        while True:
            try:
                writePort.write(writeString.encode())

            except:
                del writePort
                writePort = serial.Serial(writeName, timeout=0)

            else:
                break


        iteration = 2




    