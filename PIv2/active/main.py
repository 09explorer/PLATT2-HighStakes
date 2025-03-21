import time
import setproctitle
import multiprocessing as mp
from subsystems.label import label
from subsystems.piCom import piCom
from subsystems.odom import odom
from subsystems.indicator import indicator
from subsystems.autonSelector import autonSelect

if __name__ == "__main__":
    
    setproctitle.setproctitle("plattCode")
    
    robotData = mp.Array('f', 30)
    
    com = mp.Process(target=piCom, args=(robotData))
    com.daemon = True
    com.start()
    
    otos = mp.Process(target=odom, args=(robotData))
    otos.daemon = True
    otos.start()

    indicate = mp.Process(target=indicator, args=(robotData))
    indicate.daemon = True
    indicate.start()

    auton = mp.Process(target=autonSelect, args=(robotData))
    auton.daemon = True
    auton.start()
    
    while True:

        if robotData[label.RESET.value] == 1:
            
            otos.terminate()
            auton.terminate()

            for i in range(len(robotData)):
                robotData[i] = 0
        
            otos.start()
            auton.start()

        time.sleep(0.01)