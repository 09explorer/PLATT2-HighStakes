#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H

#include "vex.h"
#include "PLATT2\robot_config\subsystems\piCom.h"
#include "PLATT2\robot_config\subsystems\ringsort.h"
#include "PLATT2\robot_config\subsystems\wallStake.h"
#include "PLATT2\HelperFunctions.h"

class DriveControl
{
    private:
    HelperFunctions helper;

    vex::motor leftDrive1;
    vex::motor leftDrive2;
    vex::motor leftDrive3;
    vex::motor leftDrive4;

    vex::motor rightDrive1;
    vex::motor rightDrive2;
    vex::motor rightDrive3;
    vex::motor rightDrive4;



     /**
     * @brief Motor group for the left drive motors
     */
    vex::motor_group leftDrive;

    /**
     * @brief Motor group for the right drive motors.
     */
    vex::motor_group rightDrive;
    
    RingSort& ringSort;

    piCom& pi;

    vex::controller controller1;

    vex::digital_out mogo;

    vex::motor intake;

    vex::digital_out intakePiston;

    vex::motor_group hooks;

    wallStakeController& wallStake;


    public:
    DriveControl(piCom& picom, RingSort& ring, wallStakeController& w);

    void PinkDriveControl();

    void PurpleDriveControl();

    void TestControl();

    void autonControl();


};

#endif