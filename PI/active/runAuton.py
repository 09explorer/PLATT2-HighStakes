import multiprocessing
import time
import communication
import setproctitle

import autons.red.pink.comp1.comp1Start
import autons.red.pink.skills.skillsStart
import autons.blue.pink.comp1.comp1Start
import autons.blue.pink.skills.skillsStart
import autons.blue.purple.comp1.comp1Start
import autons.blue.purple.skills.skillsStart
import autons.red.purple.comp1.comp1Start
import autons.red.purple.skills.skillsStart

def start():
    
    setproctitle.setproctitle('PlattCode')
    print("started", flush=True)
    
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
                
                autons.red.pink.skills.skillsStart.skillsStart(robotData)

                pass
        
        #Blue
        elif robotData[communication.label.ALLIANCE.value] == 2:
            
            #Comp1
            if robotData[communication.label.AUTON.value] == 1:

                autons.blue.pink.comp1.comp1Start.comp1Start(robotData)
                
                pass
           
            #Skills
            elif robotData[communication.label.AUTON.value] == 2:
                
                autons.blue.pink.skills.skillsStart.skillsStart(robotData)

                pass
    
    #purple
    elif robotData[communication.label.NAME.value] == 2: 
        
        #Red
        if robotData[communication.label.ALLIANCE.value] == 1: 

            #comp1 
            if robotData[communication.label.AUTON.value] == 1:
               
               autons.red.purple.comp1.comp1Start.comp1Start(robotData)
               
               pass

            #skills
            elif robotData[communication.label.AUTON.value] == 2:
                
                autons.red.purple.skills.skillsStart.skillsStart(robotData)

                pass

        #Blue    
        elif robotData[communication.label.ALLIANCE.value] == 2:

            #comp1 
            if robotData[communication.label.AUTON.value] == 1:
               
                autons.blue.purple.comp1.comp1Start.comp1Start(robotData)

                pass

            #skills
            elif robotData[communication.label.AUTON.value] == 2:
                
                autons.blue.purple.skills.skillsStart.skillsStart(robotData)

                pass


if __name__ == '__main__':
    start()