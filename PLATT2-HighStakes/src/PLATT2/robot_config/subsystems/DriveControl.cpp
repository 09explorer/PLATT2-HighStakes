#include "PLATT2\robot_config\subsystems\DriveControl.h"
//#include "vex.h"


vex::brain Brain;

DriveControl::DriveControl(vex::motor_group& leftD, vex::motor_group& rightD, RingSort& ringS, vex::controller& con, piCom& picom, vex::digital_out& m, vex::motor& i, vex::digital_out& ip,  vex::motor& l):
leftDrive{leftD},
rightDrive{rightD},
ringSort{ringS},
controller1{con},
pi{picom},
mogo{m},
intake{i}, 
intakePiston{ip},
hooks{l}
{
    leftDrive.setVelocity(0, vex::percent);
    rightDrive.setVelocity(0, vex::percent);
}

void DriveControl::TestControl(){

    int leftDrivePower;
    int rightDrivePower;
    
    
    leftDrive.spin(vex::forward, 0, vex::rpm);
    rightDrive.spin(vex::forward, 0, vex::rpm);
    
    while(true){
      // Drive velocities

      leftDrivePower = (controller1.Axis3.position(vex::percent) + controller1.Axis1.position(vex::percent));
      rightDrivePower = (controller1.Axis3.position(vex::percent) - controller1.Axis1.position(vex::percent));

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

  leftDrive.spin(vex::forward, 0, vex::rpm);
  rightDrive.spin(vex::forward, 0, vex::rpm);
  intake.spin(vex::forward, 0, vex::rpm);
  hooks.spin(vex::forward, 0, vex::rpm);


  intakePiston.set(true);



  while (true){
        
    mogo.set((int)pi.getValue(CLAMP));

    intake.setVelocity(pi.getValue(INTAKE), vex::percent);

    hooks.setVelocity(pi.getValue(HOOKS), vex::percent);
  
    leftDrive.setVelocity(pi.getValue(LEFTVEL), vex::percent);
    rightDrive.setVelocity(pi.getValue(RIGHTVEL), vex::percent);

    vex::this_thread::sleep_for(1);
  } 
}