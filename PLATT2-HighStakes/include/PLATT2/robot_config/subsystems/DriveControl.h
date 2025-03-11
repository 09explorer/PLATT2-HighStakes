#ifndef DRIVECONTROL_H
#define DRIVECONTROL_H

#include "vex.h"
#include "PLATT2\robot_config\subsystems\piCom.h"
#include "PLATT2\robot_config\subsystems\ringsort.h"
#include "PLATT2\robot_config\subsystems\wallStake.h"
#include "PLATT2\HelperFunctions.h"

/// @brief A struct to represent the driver profile.
struct DriverProfile {
    vex::controller* controller;  // Reference to the controller

    vex::controller::button* intakeButton;
    vex::controller::button* mogoButton;
    vex::controller::button* wallStakeUpperButton;
    vex::controller::button* wallStakeLowerButton;
    vex::controller::button* ringSortButton;
    vex::controller::button* intakePistonButton;
    vex::controller::button* hookButton;
    vex::controller::button* hangHooksButton;
};


/// @brief A class to control the drive system of the robot.
class DriveControl
{
    private:
    /// @brief Three-wire port for connecting sensors and other devices.
    vex::triport ThreeWirePort = vex::triport(vex::PORT22);
    
    /// @brief Helper functions object.
    HelperFunctions helper;

    /// @brief Motor for the first left drive.
    vex::motor leftDrive1;
    
    /// @brief Motor for the second left drive.
    vex::motor leftDrive2;
    
    /// @brief Motor for the third left drive.
    vex::motor leftDrive3;
    
    /// @brief Motor for the fourth left drive.
    vex::motor leftDrive4;

    /// @brief Motor for the first right drive.
    vex::motor rightDrive1;
    
    /// @brief Motor for the second right drive.
    vex::motor rightDrive2;
    
    /// @brief Motor for the third right drive.
    vex::motor rightDrive3;
    
    /// @brief Motor for the fourth right drive.
    vex::motor rightDrive4;

    /// @brief Reference to the brain object.
    vex::brain& Brain;
    
    /// @brief Motor group for the left drive motors.
    vex::motor_group leftDrive;

    /// @brief Motor group for the right drive motors.
    vex::motor_group rightDrive;
    
    /// @brief Reference to the ring sort subsystem.
    RingSort& ringSort;

    /// @brief Reference to the Pi communication object.
    /// @brief Controller object.
    vex::controller controller1 = vex::controller(vex::primary);

    /// @brief Digital output for controlling the mogo.
    vex::digital_out mogo;

    /// @brief Motor for the intake.
    vex::motor intake;

    /// @brief Digital output for controlling the intake piston.
    vex::digital_out intakePiston;

    /// @brief Motor group for the hooks.
    vex::motor_group hooks;

    /// @brief Reference to the wall stake controller object.
    wallStakeController& wallStake;
    
    public:
    /// @brief Constructs the DriveControl class.
    /// @param picom Reference to the Pi communication object.
    /// @param ring Reference to the ring sort subsystem.
    /// @param w Reference to the wall stake controller object.
    /// @param b Reference to the brain object.
    DriveControl(RingSort& ring, wallStakeController& w, vex::brain& b);

    /// @brief Controls the drive system for the pink robot configuration.
    void PinkDriveControl();

    /// @brief Controls the drive system for the purple robot configuration.
    void PurpleDriveControl();

    /// @brief Controls the drive system for testing purposes.
    void TestControl();

    /// @brief Controls the drive system during autonomous mode.
    void autonControl();

    /// @brief Initializes the drivetrain.
    void initDrivetrain();

    /// @brief Controls the drive system for the default robot configuration.
    void defaultControl();
};

#endif