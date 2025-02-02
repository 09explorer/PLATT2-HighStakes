#include "PLATT2\robot_config\subsystems\DriveControl.h"
//#include "vex.h"

DriveControl::DriveControl(piCom& picom, RingSort& ring, wallStakeController& w, vex::brain& b):
Brain{b},
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
mogo{ThreeWirePort.A},
intake(vex::PORT3, vex::gearSetting::ratio6_1, true), 
intakePiston{ThreeWirePort.B},
wallStake{w}
{

}

void DriveControl::TestControl(){

    bool mogoOldState = true;
    bool mogoNewState = true;
    bool mogoCurrentState = false;
    bool intakeCurrentState = false;
    bool intakeOldState = true;
    bool intakeNewState = true;

    int leftDrivePower = 0;
    int rightDrivePower = 0;
    
    
    leftDrive.spin(vex::forward, 0, vex::rpm);
    rightDrive.spin(vex::forward, 0, vex::rpm);

    wallStake.setPosition(SCORE);
    ringSort.setRing(RED_RING);
    
    while(true){
      int foo = wallStake.getPosition();
    Brain.Screen.setCursor(5,1);
    Brain.Screen.print("current wall steak: %d", foo);
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

      double wallpos = wallStake.getMotor2Position();
      double wall2pos = wallStake.getMotor3Position();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Wall pos: %f", wallpos);
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("2nd Wall pos: %f", wall2pos);
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
    ringSort.setRing((RingColor)pi.getValue(COLORSORT));
    wallStake.setPosition((Position)pi.getValue(WALLSTAKE));
    ringSort.moveHooks(pi.getValue(HOOKS));
  
    leftDrive.setVelocity(pi.getValue(LEFTVEL), vex::percent);
    rightDrive.setVelocity(pi.getValue(RIGHTVEL), vex::percent);

    vex::this_thread::sleep_for(1);
  } 
}