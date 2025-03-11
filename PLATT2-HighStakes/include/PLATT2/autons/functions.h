#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "PLATT2/robot_config/subsystems/odometry.h"

class Functions {

    public:

        double* intersect(double[2], double[2], double);
        int sgn(double);
        double pythag(double[2], double[2]);

        
        
    private:
        double oldSolution[2];

        Odometry odom;

        void startOdom();

        &Odometry getOdom();






};

#endif
