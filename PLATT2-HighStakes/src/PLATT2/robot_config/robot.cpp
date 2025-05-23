#include "PLATT2/robot_config/robot.h"

Robot::Robot(vex::competition& comp):
m_Competition{comp},
brain(),
wallstakeControl(),
ringSort(brain),
driveControl(ringSort, wallstakeControl, brain),
menu(brain, m_Competition, pi)
{
    // Set default config
    robotID = NO_ROBOT;
    allianceID = NO_ALLIANCE;
    autonID = NO_AUTON;
}

void Robot::setAllianceID(AllianceConfig newID)
{
    allianceID = newID;
}

AllianceConfig Robot::getAllianceID()
{
    return allianceID;
}

void Robot::setRobotID(RobotConfig newID)
{
    robotID = newID;
}

RobotConfig Robot::getRobotID()
{
    return robotID;
}

void Robot::setAutonID(AutonConfig newID)
{
    autonID = newID;
}

AutonConfig Robot::getAutonID()
{
    return autonID;
}

void Robot::runDriveControl()
{
    buildRobotConfig();
    driveControl.initDrivetrain();
    switch(robotID)
    {
        case NO_ROBOT:
        {
            driveControl.defaultControl();
        }
        case PINK:
        {
            driveControl.PinkDriveControl();
        }
        case PURPLE:
        {
            driveControl.PurpleDriveControl();
        }
    }
}

void Robot::runAutonControl(){
    // run auto
    driveControl.autonControl();
}

wallStakeController& Robot::getWall(){
    return wallstakeControl;

}

RingSort& Robot::getRings(){
    return ringSort;

}

AutonSelector& Robot::getMenu(){
    return menu;
}

void Robot::initalizeRobot(){
    menu.drawMenu();
}

void Robot::buildRobotConfig(){
    std::vector<int> configs = menu.getSelectedValues();
    autonID = (AutonConfig)configs[0];
    allianceID = (AllianceConfig)configs[1];
    robotID = (RobotConfig)configs[2];
}