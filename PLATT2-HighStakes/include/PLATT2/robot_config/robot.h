#ifndef ROBOT_H
#define ROBOT_H

#include <vector>

#include "vex.h"
#include "PLATT2\robot_config\subsystems\ringsort.h"
#include "PLATT2\robot_config\subsystems\DriveControl.h"
#include "PLATT2\robot_config\subsystems\piCom.h"
#include "PLATT2\robot_config\subsystems\WallStake.h"
#include "PLATT2\robot_config\Autonselector.h"

/**
 * @brief Enumeration to represent the 2 different robot configurations with a default option.
 */
enum RobotConfig
{
    NO_ROBOT = 0,
    PINK = 1,
    PURPLE = 2
    
};

/**
 * @brief Enumeration to represent the 2 alliance colors with a default option.
 */
enum AllianceConfig
{
    NO_ALLIANCE = 0,
    RED = 1,
    BLUE = 2
    
};

/**
 * @brief Enumeration to represent the 6 different autonomous modes the robot may operate in with a non auton option.
 */
enum AutonConfig
{

    NO_AUTON = 0,
    COMP_1 = 1,
    SKILLS_1 = 2

};

/**
 * @brief Class to represent the robot system. Contains all subsystems and controls needed for robot operation.
 * @authors Dominic Young & Logan Wolf
 */
class Robot
{
    private:

    /**
     * @brief The competition object.
     */
    vex::competition& m_Competition;

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
    //vex::brain brain;

    /**
     * @brief The wall stake subsystem object.
     */
    wallStakeController wallstakeControl;

    /**
     * @brief The drive control subsystem object.
     */
    DriveControl driveControl;

    /**
     * @brief The Pi communication object.
     */
    piCom pi;    

    /**
     * @brief The brain menu object.
     */
    AutonSelector menu;

    public:
    
    /**
     * @brief Constructs the Robot class.
     */
    Robot(vex::competition& comp);
    
    /**
     * @brief The robot brain.
     */
    vex::brain brain;

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
    
    /**
     * @brief Runs the autonomous control.
     */
    void runAutonControl();

    /**
     * @brief Runs the drive control.
     */
    void runDriveControl();

    /**
     * @brief Gets the Pi communication object.
     * @return Reference to the Pi communication object.
     */
    piCom& getPi();

    /**
     * @brief Gets the wall stake controller object.
     * @return Reference to the wall stake controller object.
     */
    wallStakeController& getWall();

    /**
     * @brief Gets the ring sort object.
     * @return Reference to the ring sort object.
     */
    RingSort& getRings();

    /**
     * @brief Initializes the robot.
     */
    void initalizeRobot();

    void buildRobotConfig();

    AutonSelector& getMenu();
};

#endif