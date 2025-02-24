import time
import setproctitle
import multiprocessing as mp
from subsystems.label import label
from subsystems.piCom import piCom
from subsystems.odom import odom
from subsystems.indicator import indicator


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

    
    
    while True:

        if robotData[label.RESET.value] == 1:
            
            com.terminate()
            otos.terminate()
            indicate.terminate()

            for i in range(len(robotData)):
                robotData[i] = 0
        
            com.start()
            otos.start()
            indicate.start()

        time.sleep(0.01)