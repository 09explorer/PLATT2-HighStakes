import multiprocessing
import communication
import setproctitle

def start():
    
    setproctitle.setproctitle('PlattCode')

    initData = communication.holdForInit()
    
    robotData = multiprocessing.Array('f', 7)

    robotData[communication.label.NAME.value] = initData[0]
    robotData[communication.label.AUTON.value] = initData[1]
    robotData[communication.label.ALLIANCE.value] = initData[2]

    p1 = multiprocessing.Process(target=communication.startLink, args=(robotData,))
    p1.daemon = True
    p1.start()

    if robotData[communication.label.NAME.value] == 1:
        if robotData[communication.label.AUTON.value] == 1:
            pass
        else:
            pass

    elif robotData[communication.label.NAME.value] == 2:
        if robotData[communication.label.AUTON.value] == 1:
            pass
        else:
            pass
        