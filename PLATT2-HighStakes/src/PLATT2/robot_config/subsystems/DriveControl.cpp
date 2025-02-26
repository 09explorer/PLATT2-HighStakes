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
intake(vex::PORT3, vex::gearSetting::ratio6_1, false), 
intakePiston{ThreeWirePort.B},
wallStake{w}
{

}

void DriveControl::initDrivetrain(){
  leftDrive.setStopping(vex::brake);
  rightDrive.setStopping(vex::brake);
  leftDrive.spin(vex::forward, 0, vex::rpm);
  rightDrive.spin(vex::forward, 0, vex::rpm);
  intake.spin(vex::forward, 0, vex::rpm);
}

void DriveControl::TestControl(){

    bool mogoOldState = true;
    bool mogoNewState = true;
    bool mogoCurrentState = false;
    bool intakeCurrentState = false;
    bool intakeOldState = true;
    bool intakeNewState = true;
    bool ROldState;
	  bool RNewState;
    bool rightWingPos = false;
    bool wasButtonPressed = false;
    bool oldPress1 = false;
    bool oldPress2 = false;

    int leftDrivePower = 0;
    int rightDrivePower = 0;
    

    leftDrive.setStopping(vex::hold);
    rightDrive.setStopping(vex::hold);

    leftDrive.spin(vex::forward, 0, vex::rpm);
    rightDrive.spin(vex::forward, 0, vex::rpm);
    intake.spin(vex::forward, 0, vex::rpm);

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

      RNewState = controller1.ButtonR1.pressing();
      
		if ( RNewState == true and ROldState == false) {
			
			rightWingPos = !rightWingPos;
		
			ROldState = true;
			
			if (rightWingPos == false){
				ringSort.moveHooks(90);
				rightWingPos = false;
				
			}
			else{
				ringSort.moveHooks(0);
				rightWingPos = true;
		
			}
		   
		}
		ROldState = RNewState;

      double wallpos = wallStake.getMotor2Position();
      double wall2pos = wallStake.getMotor3Position();
      Brain.Screen.setCursor(1,1);
      Brain.Screen.print("Wall pos: %f", wallpos);
      Brain.Screen.setCursor(2,1);
      Brain.Screen.print("2nd Wall pos: %f", wall2pos);

    // Intake Control
    if (controller1.ButtonL1.pressing())
    {
      intake.setVelocity(100, vex::pct);
    }
    else
    {
      intake.setVelocity(0, vex::pct);
    }


            // Check the current state of the button
        bool isButtonPressed = controller1.ButtonDown.pressing();

        // Detect a new press (button transitioning from not pressed to pressed)
        if (isButtonPressed && !wasButtonPressed) {
           ringSort.incrementColor();
        }

        // Update the state for the next iteration
        wasButtonPressed = isButtonPressed;

        if(controller1.ButtonB.pressing())
    {
      if (oldPress1 == false){
      wallStake.incrementPosHigh();

      }
      oldPress1 = true;
    }else{

      oldPress1 = false;

    }

    if(controller1.ButtonY.pressing())
    {
      if (oldPress2 == false){
      wallStake.incrementPosLow();

      }
      oldPress2 = true;
    }else{

      oldPress2 = false;

    }

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
  
  //leftDrive.spin(vex::forward, 0, vex::rpm);
  //rightDrive.spin(vex::forward, 0, vex::rpm);
  intake.spin(vex::forward, 0, vex::rpm);
  hooks.spin(vex::forward, 0, vex::rpm);

  while (true){
        
    mogo.set((int)pi.getValue(CLAMP));
    intakePiston.set((int)pi.getValue(INTAKEPISTON));
    intake.setVelocity(pi.getValue(INTAKE), vex::percent);
    ringSort.setRing((RingColor)pi.getValue(COLORSORT));
    wallStake.setPosition((Position)pi.getValue(WALLSTAKE));
    ringSort.moveHooks(pi.getValue(HOOKS));
  
    leftDrive.spin(vex::forward, (pi.getValue(LEFTVEL)/100)*12, vex::volt);
    rightDrive.spin(vex::forward, (pi.getValue(RIGHTVEL)/100)*12, vex::volt);

    //leftDrive.setVelocity(pi.getValue(LEFTVEL), vex::percent);
    //rightDrive.setVelocity(pi.getValue(RIGHTVEL), vex::percent);

    vex::this_thread::sleep_for(1);
  } 
}