import time
from autons.red.purple.comp1 import goalRush
from autons.red.purple.comp1.allianceStake import allianceStake
from autons.red.purple.comp1.corner import corner
from autons.red.purple.comp1.ladder import ladder
from subsystems.label import label

def start(robotData):
    
    startTime = time.time()

    goalRush.goalRush(robotData)
    allianceStake(robotData)
    corner(robotData)
    ladder(robotData)

    print(time.time()-startTime, flush=True)

