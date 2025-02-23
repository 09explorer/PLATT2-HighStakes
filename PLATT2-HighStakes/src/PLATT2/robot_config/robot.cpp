#include "PLATT2/robot_config/robot.h"

Robot::Robot():
brain(),
pi(),
wallstakeControl(),
ringSort(brain),
driveControl(pi, ringSort, wallstakeControl, brain),
menu(brain)
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
    switch(autonID){
        case NO_AUTON:
        {
            driveControl.TestControl();
        }
        case RED:
        {
         //   driveControl.RedAutonControl();
        }
        case BLUE:
        {
           // driveControl.BlueAutonControl();
        }
    }

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
    std::vector<int> selectedValues = menu.getSelectedValues();
    autonID = static_cast<AutonConfig>(selectedValues[0]);
    allianceID = static_cast <AllianceConfig>(selectedValues[1]);
    robotID = static_cast<RobotConfig>(selectedValues[2]);
}