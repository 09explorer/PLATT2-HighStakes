#include "PLATT2\robot_config\subsystems\DriveControl.h"
//#include "vex.h"


vex::brain Brain;

DriveControl::DriveControl(vex::motor_group& leftD, vex::motor_group& rightD, RingSort& ringS, vex::controller& con, piCom& picom, Odometry& o, vex::digital_out& m, vex::motor& i, vex::digital_out& ip):
leftDrive{leftD},
rightDrive{rightD},
ringSort{ringS},
controller1{con},
pi{picom},
odom{o},
mogo{m},
intake{i}, 
intakePiston{ip}
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
      Brain.Screen.clearScreen();
      Brain.Screen.setCursor(3,1);
      Brain.Screen.print((double)odom.cPos[0]);
      Brain.Screen.setCursor(4,1);
      Brain.Screen.print((double)odom.cPos[1]);
      Brain.Screen.setCursor(5,1);
      Brain.Screen.print((double)odom.heading);


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

  intakePiston.set(true);



  while (true){
    
    Brain.Screen.clearScreen();
    Brain.Screen.setCursor(3,1);
    Brain.Screen.print((double)pi.getValue(LEFTVEL));
    Brain.Screen.setCursor(4,1);
    Brain.Screen.print((double)pi.getValue(RIGHTVEL));
    
    pi.setValue(XPOS, odom.cPos[0]);
    pi.setValue(YPOS, odom.cPos[1]);
    pi.setValue(HEADING, odom.heading);

    mogo.set((int)pi.getValue(CLAMP));

    intake.setVelocity(pi.getValue(INTAKE), vex::percent);
  
    leftDrive.setVelocity(pi.getValue(LEFTVEL), vex::percent);
    rightDrive.setVelocity(pi.getValue(RIGHTVEL), vex::percent);

    vex::this_thread::sleep_for(1);
  } 
}