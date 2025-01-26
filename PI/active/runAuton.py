import multiprocessing
import time
import autons.red.pink.comp1.comp1Start
import communication
import setproctitle
import functions.vision as vision
import autons.red.pink.comp1.comp1Start

def start():
    
    setproctitle.setproctitle('PlattCode')
    print("started")
    
    robotData = multiprocessing.Array('f', 20)

    p1 = multiprocessing.Process(target=communication.startLink, args=(robotData,))
    p1.daemon = True
    p1.start()

    while robotData[communication.label.FLAG.value] == 0:
        time.sleep(0.01)
    
    print("recived flag", flush=True)
    
    #pink
    if robotData[communication.label.NAME.value] == 1: 
        
        #Red
        if robotData[communication.label.ALLIANCE.value] == 1:
            
            #Comp1
            if robotData[communication.label.AUTON.value] == 1:
                

                autons.red.pink.comp1.comp1Start.comp1Start(robotData)

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