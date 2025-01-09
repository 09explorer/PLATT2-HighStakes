#ifndef ROBOT_H
#define ROBOT_H

#include "vex.h"
#include "PLATT2\robot_config\subsystems\ringsort.h"
#include "PLATT2\robot_config\subsystems\DriveControl.h"
#include "PLATT2\robot_config\subsystems\piCom.h"

/**
 * @brief Enumeration to represent the 2 different robot configurations with a default option.
 */
enum RobotConfig
{
    PINK = 1,
    PURPLE = 2,
    NO_ROBOT = 3
};

/**
 * @brief Enumeration to represent the 2 alliance colors with a default option.
 */
enum AllianceConfig
{
    RED = 1,
    BLUE = 2,
    NO_ALLIANCE = 3
};

/**
 * @brief Enumeration to represent the 6 different autonomous modes the robot may operate in with a non auton option.
 */
enum AutonConfig
{
    PINK_RED = 1,
    PINK_BLUE = 2,
    PURPLE_RED = 3,
    PURPLE_BLUE = 4,
    PINK_SKILLS = 5,
    PURPLE_SKILLS = 6,
    NO_AUTON = 7
};

/**
 * @brief Class to represent the robot system. Contains all subsystems and controls needed for robot operation.
 * @authors Dominic Young & Logan Wolf
 */
class Robot
{
    private:

    /**
     * @brief The ID of the robot.
     */
    RobotConfig robotID;

    /**
     * @brief The ID of the current alliance.
     */
    AllianceConfig allianceID;

    /**
     * @brief The ID of the desired autonomous routine to run.
     */
    AutonConfig autonID;

    /**
     * @brief Reference to the ring sort subsystem.
     */
    RingSort ringSort;

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

    vex::optical opticalSensor;

    vex::inertial inert;

    vex::digital_out ringsortPiston;

    vex::motor lift1;

    vex::motor lift2;

    DriveControl driveControl;

    piCom pi;

    public:

    Robot();

    /**
     * @brief Sets the current alliance ID.
     * @param newID The desired alliance to set to.
     */
    void setAllianceID(AllianceConfig newID);

    /**
     * @brief Gets the current alliance ID.
     * @return The current alliance ID enum.
     */
    AllianceConfig getAllianceID();

    /**
     * @brief Sets the current robot ID.
     * @param newID The desired new ID.
     */
    void setRobotID(RobotConfig newID);

    /**
     * @brief Gets the current ID of the robot.
     * @return The current ID of the robot.
     */
    RobotConfig getRobotID();

    /**
     * @brief Sets the ID of the autonomous routine to run.
     * @param newID The autonomous ID to use.
     */
    void setAutonID(AutonConfig newID);

    /**
     * @brief Gets the current ID of the autonomous routine.
     * @return The current autonomous routine ID.
     */
    AutonConfig getAutonID();

    void runDriveControl();
};

#endif