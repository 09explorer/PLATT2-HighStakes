#include "PLATT2/robot_config/robot.h"

Robot::Robot():
leftDrive1(vex::PORT1, vex::gearSetting::ratio6_1, false),
leftDrive2(vex::PORT2, vex::gearSetting::ratio6_1, true),
leftDrive3(vex::PORT11, vex::gearSetting::ratio6_1, true),
leftDrive4(vex::PORT13, vex::gearSetting::ratio6_1, false),
rightDrive1(vex::PORT16, vex::gearSetting::ratio6_1, true),
rightDrive2(vex::PORT17, vex::gearSetting::ratio6_1, false),
rightDrive3(vex::PORT18, vex::gearSetting::ratio6_1, false),
rightDrive4(vex::PORT19, vex::gearSetting::ratio6_1, true),
leftDrive(leftDrive1, leftDrive2, leftDrive3, leftDrive4),
rightDrive(rightDrive1, rightDrive2, rightDrive3, rightDrive4),
opticalSensor(vex::PORT10),
ringsortPiston(brain.ThreeWirePort.C),
intakePiston(brain.ThreeWirePort.B),
intake(vex::PORT3, vex::gearSetting::ratio6_1, true),
mogoPistion(brain.ThreeWirePort.A),
lift1(vex::PORT4, vex::gearSetting::ratio6_1, false),
lift2(vex::PORT13, vex::gearSetting::ratio6_1, false),
ringSort(lift1, lift2, opticalSensor, ringsortPiston, brain),
wallstake1(vex::PORT20, vex::gearSetting::ratio6_1, true),
wallstake2(vex::PORT9, vex::gearSetting::ratio6_1, false),
wallstake3(vex::PORT5, vex::gearSetting::ratio6_1, true),
wallstakeControl(wallstake1,wallstake2,wallstake3),
driveControl(leftDrive, rightDrive, ringSort, controller, pi, mogoPistion, intake, intakePiston, lift1, wallstakeControl)

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

void Robot::initalizeRobot(){
    
    leftDrive.setStopping(vex::brake);
    rightDrive.setStopping(vex::brake);
    
    


}