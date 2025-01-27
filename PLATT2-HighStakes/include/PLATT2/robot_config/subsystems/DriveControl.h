#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H

#include "vex.h"
#include "PLATT2\robot_config\subsystems\piCom.h"
#include "PLATT2\robot_config\subsystems\ringsort.h"
#include "PLATT2\robot_config\subsystems\Odometry.h"

class DriveControl
{
    private:
     /**
     * @brief Motor group for the left drive motors
     */
    vex::motor_group& leftDrive;

    /**
     * @brief Motor group for the right drive motors.
     */
    vex::motor_group& rightDrive;
    
    RingSort& ringSort;

    piCom& pi;

    Odometry& odom;

    vex::controller& controller1;


    public:
    DriveControl(vex::motor_group& leftD, vex::motor_group& rightD, RingSort& ringS, vex::controller& con, piCom& picom, Odometry& o);

    void PinkDriveControl();

    void PurpleDriveControl();

    void TestControl();

    void autonControl();


};

#endif