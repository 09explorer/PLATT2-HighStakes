import multiprocessing
import time
import communication
import setproctitle

def start():
    
    setproctitle.setproctitle('PlattCode')
    print("started")
    
    robotData = multiprocessing.Array('f', 20)

    p1 = multiprocessing.Process(target=communication.startLink, args=(robotData,))
    p1.daemon = True
    p1.start()

    while robotData[communication.label.FLAG.value] == 0:
        time.sleep(0.01)
    
    print("recived flag")
    
    #pink
    if robotData[communication.label.NAME.value] == 1: 
        
        #Blue
        if robotData[communication.label.ALLIANCE.value] == 1:
            
            #Comp1
            if robotData[communication.label.AUTON.value] == 1:
                print("at data", flush=True)
                robotData[communication.label.LEFTVEL.value] = 20
                robotData[communication.label.RIGHTVEL.value] = 20
                print(robotData[communication.label.LEFTVEL.value], flush=True)
                time.sleep(1)


                robotData[communication.label.LEFTVEL.value] = 0
                robotData[communication.label.RIGHTVEL.value] = 0

                print("finished", flush=True)



                pass
            
            #Skills
            elif robotData[communication.label.AUTON.value] == 2:
                
                pass
        
        #Blue
        elif robotData[communication.label.ALLIANCE.value] == 2:
            
            #Comp1
            if robotData[communication.label.AUTON.value] == 1:
                
                pass
           
            #Skills
            elif robotData[communication.label.AUTON.value] == 2:
                
                pass
    
    #purple
    elif robotData[communication.label.NAME.value] == 2: 
        
        #Red
        if robotData[communication.label.ALLIANCE.value] == 1: 

            #comp1 
            if robotData[communication.label.AUTON.value] == 1:
               
               pass

            #skills
            elif robotData[communication.label.AUTON.value] == 2:
                
                pass

        #Blue    
        elif robotData[communication.label.ALLIANCE.value] == 2:

            #comp1 
            if robotData[communication.label.AUTON.value] == 1:
               
               pass

            #skills
            elif robotData[communication.label.AUTON.value] == 2:
                
                pass


if __name__ == '__main__':
    start()