#include "PLATT2\robot_config\subsystems\DriveControl.h"
//#include "vex.h"


vex::brain Brain;

DriveControl::DriveControl(piCom& picom, RingSort& ring, wallStakeController& w):
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
ringSort{ring},
controller1(vex::primary),
pi{picom},
mogo{Brain.ThreeWirePort.A},
intake(vex::PORT3, vex::gearSetting::ratio6_1, true), 
intakePiston{Brain.ThreeWirePort.B},
wallStake{w}
{
    leftDrive.setVelocity(0, vex::percent);
    rightDrive.setVelocity(0, vex::percent);
}

void DriveControl::TestControl(){
    bool mogoOldState;
    bool mogoNewState;
    bool mogoCurrentState;
    bool intakeCurrentState;
    bool intakeOldState;
    bool intakeNewState;


    int leftDrivePower;
    int rightDrivePower;
    
    
    leftDrive.spin(vex::forward, 0, vex::rpm);
    rightDrive.spin(vex::forward, 0, vex::rpm);

    //wallStake.position = SCORE;
    
    while(true){
      // Drive velocities

      leftDrivePower = (controller1.Axis3.position(vex::percent) + controller1.Axis1.position(vex::percent));
      rightDrivePower = (controller1.Axis3.position(vex::percent) - controller1.Axis1.position(vex::percent));

      leftDrive.setVelocity(leftDrivePower, vex::percent);
      rightDrive.setVelocity(rightDrivePower, vex::percent);

        // Mogo toggle
      mogoNewState = controller1.ButtonL2.pressing();
      helper.solenoidToggle(mogoCurrentState, mogoNewState, mogoOldState, mogo);

      intakeNewState = controller1.ButtonRight.pressing();
      helper.solenoidToggle(intakeOldState,intakeNewState,intakeCurrentState, intakePiston);

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
  wallStake.setPosition(HOME);


  while (true){
        
    mogo.set((int)pi.getValue(CLAMP));

    intake.setVelocity(pi.getValue(INTAKE), vex::percent);

    hooks.setVelocity(pi.getValue(HOOKS), vex::percent);
  
    leftDrive.setVelocity(pi.getValue(LEFTVEL), vex::percent);
    rightDrive.setVelocity(pi.getValue(RIGHTVEL), vex::percent);

    vex::this_thread::sleep_for(1);
  } 
}