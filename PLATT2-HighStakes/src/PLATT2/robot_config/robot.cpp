#include "PLATT2/robot_config/robot.h"

Robot::Robot():
wallstakeControl(),
driveControl(pi, ringSort, wallstakeControl)

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
    robotID = NO_ROBOT;
    switch(robotID)
    {
        case NO_ROBOT:
        {
            driveControl.TestControl();
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

   // while (true)
   // {
//
   //     brain.Screen.printAt(1, 20, "in loop, we are at %f",wallstake1.position(vex::rev));
   // }
    

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

void Robot::initalizeRobot(){
    
}