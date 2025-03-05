#include "PLATT2/robot_config/robot.h"

Robot::Robot(vex::competition& comp):
m_Competition{comp},
brain(),
pi(),
wallstakeControl(),
ringSort(brain),
driveControl(pi, ringSort, wallstakeControl, brain),
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

piCom& Robot::getPi(){
    return pi;
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

}