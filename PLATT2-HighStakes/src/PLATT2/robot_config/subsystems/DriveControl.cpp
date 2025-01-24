#include "PLATT2\robot_config\subsystems\DriveControl.h"
//#include "vex.h"




DriveControl::DriveControl(vex::motor_group& leftD, vex::motor_group& rightD, RingSort& ringS, vex::controller& con, piCom& picom):
leftDrive{leftD},
rightDrive{rightD},
ringSort{ringS},
controller1{con},
pi{picom}
{
    leftDrive.setVelocity(0, vex::percent);
    rightDrive.setVelocity(0, vex::percent);
}

void DriveControl::TestControl()
{
    while(true){
      // Drive velocities
    int leftDrivePower = (controller1.Axis3.position(vex::percent) + controller1.Axis1.position(vex::percent));
    int rightDrivePower = (controller1.Axis3.position(vex::percent) - controller1.Axis1.position(vex::percent));

    leftDrive.setVelocity(leftDrivePower, vex::percent);
    rightDrive.setVelocity(rightDrivePower, vex::percent);

    vex::this_thread::sleep_for(20); // Sleep the task for a short amount of time
    }
}

void DriveControl::PinkDriveControl()
{

}

void DriveControl::PurpleDriveControl()
{
  
}

void DriveControl::autonControl(){

  pi.setValue(FLAG, 1);

  while (true){
    //Brain.Screen.clearScreen();
    //Brain.Screen.setCursor(3,1);
    //Brain.Screen.print((double)pi.getValue(FLAG));

    leftDrive.setVelocity(pi.getValue(LEFTVEL), vex::percent);
    rightDrive.setVelocity(pi.getValue(RIGHTVEL), vex::percent);


    vex::this_thread::sleep_for(10);
  }
}