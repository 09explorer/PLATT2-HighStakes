#include "PLATT2\robot_config\subsystems\Odometry.h"
#include "vex.h"
#include <cmath>

Odometry::Odometry(vex::brain& b, vex::rotation& x, vex::rotation& y, vex::inertial& i):
Brain{b},
x_od{x},
y_od{y},
inert{i}
{

};

void Odometry::tracking(){
    inert.setHeading(270, vex::rotationUnits::deg);

    //init variables
    double oldX = 0;
    double oldY = 0;

    while(true){

        heading = 360 - inert.heading();

        if (heading < 0){heading = heading + 360;}

        cPos[1] =( cPos[1] - (((x_od.position(ENCODER_UNITS)-oldX)/360*CIRCUM)*cos(PI*(heading/180))));
        cPos[1] =( cPos[1] + (((y_od.position(ENCODER_UNITS)-oldY)/360*CIRCUM)*sin(PI*(heading/180))));
        
        cPos[0] =( cPos[0] + (((y_od.position(ENCODER_UNITS)-oldY)/360*CIRCUM)*cos(PI*(heading/180))));
        cPos[0] = (cPos[0] + (((x_od.position(ENCODER_UNITS)-oldX)/360*CIRCUM)*sin(PI*(heading/180))));

        oldX = x_od.position(ENCODER_UNITS);
        oldY = y_od.position(ENCODER_UNITS);
      
        vex::this_thread::sleep_for(10);
    }
} 