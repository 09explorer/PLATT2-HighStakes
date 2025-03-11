#ifndef ODOMETRY_H
#define ODOMETRY_H

#include "vex.h"
#include <cmath>

class Odometry{


    public:
        
        void trackingAlg();
        double* getPos();
        double getHeading();    
    
    private:

        double heading;
        double cPos[2];

        double oldX = 0;
        double oldY = 0;

        vex::rotation y_od = vex::rotation(vex::PORT6);
        vex::inertial inert = vex::inertial(vex::PORT7);


};

#endif