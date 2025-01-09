#include "PLATT2\robot_config\robot.h"

Robot::Robot():
leftDrive1(vex::PORT1, vex::gearSetting::ratio6_1, false),
leftDrive2(vex::PORT2, vex::gearSetting::ratio6_1, true),
leftDrive3(vex::PORT11, vex::gearSetting::ratio6_1, true),
leftDrive4(vex::PORT12, vex::gearSetting::ratio6_1, false),
rightDrive1(vex::PORT16, vex::gearSetting::ratio6_1, true),
rightDrive2(vex::PORT17, vex::gearSetting::ratio6_1, false),
rightDrive3(vex::PORT18, vex::gearSetting::ratio6_1, false),
rightDrive4(vex::PORT19, vex::gearSetting::ratio6_1, true),
leftDrive(leftDrive1, leftDrive2, leftDrive3, leftDrive4),
rightDrive(rightDrive1, rightDrive2, rightDrive3, rightDrive4),
opticalSensor(vex::PORT10),
ringsortPiston(brain.ThreeWirePort.A),
lift1(vex::PORT12, vex::gearSetting::ratio6_1, true),
lift2(vex::PORT13, vex::gearSetting::ratio6_1, false),
inert(vex::PORT14),
ringSort(lift1, lift2, opticalSensor, ringsortPiston, brain),
driveControl(leftDrive, rightDrive, ringSort, controller, pi)
{
    // Set default config
    robotID = NO_ROBOT;
    allianceID = NO_ALLIANCE;
    autonID = NO_AUTON;

    // Calibrate IMU
    inert.calibrate();
    while(inert.isCalibrating()){
        vex::this_thread::sleep_for(100);
    }
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