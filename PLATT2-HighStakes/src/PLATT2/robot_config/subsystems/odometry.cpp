#include "PLATT2/robot_config/subsystems/odometry.h"

void Odometry::trackingAlg(){

    const double pi = 3.141592654;
    const double circum = 8.639379797;

        while(true){

            heading = 360 + -inert.heading();
            
           
            cPos[1] = cPos[1] + (((y_od.position(vex::deg)-oldY)/360*circum)*sin(pi*(heading/180)));
           
            cPos[0] = cPos[0] + (((y_od.position(vex::deg)-oldY)/360*circum)*cos(pi*(heading/180)));
            


            oldY = y_od.position(vex::deg);
            
            vex::this_thread::sleep_for(10);
    }

}   

double* Odometry::getPos(){

    static double position[2];

    position[0] = this->cPos[0];
    position[1] = this->cPos[1];

    return position;

}

double Odometry::getHeading(){

    return this->heading;

}
