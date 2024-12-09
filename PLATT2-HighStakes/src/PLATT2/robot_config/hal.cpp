#include "PLATT2\robot_config\hal.h"

Hal::Hal() : 
leftDrive1(vex::PORT1, vex::gearSetting::ratio6_1, true),
leftDrive2(vex::PORT2, vex::gearSetting::ratio6_1, false),
leftDrive3(vex::PORT3, vex::gearSetting::ratio6_1, true),
leftDrive4(vex::PORT4, vex::gearSetting::ratio6_1, false),
rightDrive1(vex::PORT5, vex::gearSetting::ratio6_1, false),
rightDrive2(vex::PORT6, vex::gearSetting::ratio6_1, true),
rightDrive3(vex::PORT7, vex::gearSetting::ratio6_1, false),
rightDrive4(vex::PORT8, vex::gearSetting::ratio6_1, true),
leftDrive(leftDrive1, leftDrive2, leftDrive3, leftDrive4),
rightDrive(rightDrive1, rightDrive2, rightDrive3, rightDrive4)
{

}

vex::motor_group Hal::getLeftDrive()
{
    return leftDrive;
}

vex::motor_group Hal::getRightDrive()
{
    return rightDrive;
}