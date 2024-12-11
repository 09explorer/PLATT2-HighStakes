#ifndef HAL_H
#define HAL_H

#include "vex.h"

/**
 * @brief Hardware abstraction layer class. Contains all hardware sensors and motors.
 * @author Dominic Young
 */
class Hal
{
    private:

    const int LEFT_DRIVE_1_PORT {1};
    const int LEFT_DRIVE_2_PORT {2};
    const int LEFT_DRIVE_3_PORT {3};
    const int LEFT_DRIVE_4_PORT {4};

    const int RIGHT_DRIVE_1_PORT {5};
    const int RIGHT_DRIVE_2_PORT {6};
    const int RIGHT_DRIVE_3_PORT {7};
    const int RIGHT_DRIVE_4_PORT {8};

    /**
     * @brief The robot brain.
     */
    vex::brain brain;

    /**
     * @brief The primary robot controller.
     */
    vex::controller controller;

    /**
     * @brief front bank front left drive motor.
     */
    vex::motor leftDrive1;

    /**
     * @brief front bank rear left drive motor.
     */
    vex::motor leftDrive2;

    /**
     * @brief rear bank front left drive motor.
     */
    vex::motor leftDrive3;

    /**
     * @brief rear bank rear left drive motor.
     */
    vex::motor leftDrive4;

    /**
     * @brief front bank front right drive motor.
     */
    vex::motor rightDrive1;
    
    /**
     * @brief front bank rear right drive motor.
     */
    vex::motor rightDrive2;

    /**
     * @brief rear bank front right drive motor.
     */
    vex::motor rightDrive3;

    /**
     * @brief rear bank rear right drive motor.
     */
    vex::motor rightDrive4;

    /**
     * @brief Motor group for the left drive motors
     */
    vex::motor_group leftDrive;

    /**
     * @brief Motor group for the right drive motors.
     */
    vex::motor_group rightDrive;

    public:

    Hal();

    /**
     * @brief Gets the motors group for the left half of the drivetrain.
     * @return The motor group containing the left drivetrain motors.
     */
    vex::motor_group getLeftDrive();

    /**
     * @brief Gets the motor group for the left half of the drivetrain
     * @return The motor group containing the right drivetrain motors.
     */
    vex::motor_group getRightDrive();

};

#endif