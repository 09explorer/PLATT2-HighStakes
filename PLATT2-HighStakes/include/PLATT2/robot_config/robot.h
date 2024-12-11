#ifndef ROBOT_H
#define ROBOT_H

#include "vex.h"
#include "PLATT2\robot_config\hal.h"
#include "PLATT2\robot_config\subsystems\ringsort.h"

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
     * @brief Reference to the HAL.
     */
    Hal& hal;

    /**
     * @brief Reference to the ring sort subsystem.
     */
    RingSort& ringSort;

    public:

    Robot(Hal& hal);

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


};

#endif