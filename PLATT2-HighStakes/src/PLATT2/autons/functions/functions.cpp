#include "PLATT2/autons/functions.h"

Odometry& pain = odom.getOdom();

void Functions::startOdom(){



    auto odomRun = [](void) {odom.trackingAlg();};
    vex::thread odomThread = vex::thread(odomRun);


}