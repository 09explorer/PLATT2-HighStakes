#include "PLATT2\robot_config\subsystems\DriveControl.h"
//#include "vex.h"

DriveControl::DriveControl(RingSort& ring, wallStakeController& w, vex::brain& b):
Brain{b},
leftDrive1(vex::PORT2, vex::gearSetting::ratio6_1, false),
leftDrive2(vex::PORT1, vex::gearSetting::ratio6_1, true),
leftDrive3(vex::PORT4, vex::gearSetting::ratio6_1, true),
leftDrive4(vex::PORT3, vex::gearSetting::ratio6_1, false),
rightDrive1(vex::PORT11, vex::gearSetting::ratio6_1, true),
rightDrive2(vex::PORT12, vex::gearSetting::ratio6_1, false),
rightDrive3(vex::PORT13, vex::gearSetting::ratio6_1, false),
rightDrive4(vex::PORT14, vex::gearSetting::ratio6_1, true),
leftDrive(leftDrive1, leftDrive2, leftDrive3, leftDrive4),
rightDrive(rightDrive1, rightDrive2, rightDrive3, rightDrive4),
ringSort{ring},
mogo{ThreeWirePort.A},
intake(vex::PORT15, vex::gearSetting::ratio6_1, false), 
intakePiston{ThreeWirePort.B},
wallStake{w},
hangHooks{ThreeWirePort.D}
{
}


void DriveControl::initDrivetrain(){
  leftDrive.setStopping(vex::brake);
  rightDrive.setStopping(vex::brake);
  leftDrive.spin(vex::forward, 0, vex::rpm);
  rightDrive.spin(vex::forward, 0, vex::rpm);
  intake.spin(vex::forward, 0, vex::rpm);
/*
  jonProfile.intakeButton = controller1.ButtonR2;
  jonProfile.mogoButton = controller1.ButtonL2;
  jonProfile.wallStakeUpperButton = controller1.ButtonB;
  jonProfile.wallStakeLowerButton = controller1.ButtonX;
  jonProfile.ringSortButton = controller1.ButtonDown;
  jonProfile.intakePistonButton = controller1.ButtonLeft;
  jonProfile.hookButton = controller1.ButtonR1;
  jonProfile.hangHooksButton = controller1.ButtonY;

  quinnProfile.intakeButton = controller1.ButtonR1; // intake
  quinnProfile.mogoButton = controller1.ButtonR2; // mogo
  quinnProfile.wallStakeUpperButton = controller1.ButtonUp; // wallstake upper
  quinnProfile.wallStakeLowerButton = controller1.ButtonDown; // wallstake lower
  quinnProfile.ringSortButton = controller1.ButtonL1; // ringsort
  quinnProfile.intakePistonButton = controller1.ButtonRight; // intake piston
  quinnProfile.hookButton = controller1.ButtonA; // hooks
  quinnProfile.hangHooksButton = controller1.ButtonY; // hang hooks*/

  }
/*
  defaultProfile = 
  {
    controller1.ButtonR2, // intake
    controller1.ButtonL2, // mogo
    controller1.ButtonB, // wallstake upper
    controller1.ButtonX, // wallstake alliance
    controller1.ButtonDown, // ringsort
    controller1.ButtonLeft, // intake piston
    controller1.ButtonR1, // hooks
    controller1.ButtonY // hang hooks
  };
*/
  
/*
  quinnProfile = 
  {
    controller1.ButtonR1, // intake
    controller1.ButtonR2, // mogo
    controller1.ButtonUp, // wallstake upper
    controller1.ButtonDown, // wallstake lower
    controller1.ButtonL1, // ringsort
    controller1.ButtonRight, // intake piston
    controller1.ButtonA, // hooks
    controller1.ButtonY // hang hooks
  };

  currentProfile = defaultProfile;
*/
void DriveControl::TestControl() {
  // State variables
  bool mogoPreviousState = true;
  bool mogoNewState;
  bool mogoCurrentState = false;
  bool intakePreviousState = true;
  bool intakeCurrentState = false;
  bool intakeNewState;
  bool hangPreviousState = true;
  bool hangNewState;
  bool hangCurrentState = false;
  bool hookPreviousState = false;
  bool hookCurrentState = false;
  bool rightHookEngaged = false;
  bool buttonPreviouslyPressed = false;
  bool xButtonPreviouslyPressed = false;
  bool yButtonPreviouslyPressed = false;
  bool ringSortButtonPreviouslyPressed = false;


  // Drive power variables
  int leftDrivePower = 0;
  int rightDrivePower = 0;
  
  wallStake.setPosition(SCORE);
  Brain.Screen.clearScreen();
  
  while (true) {
      int wallStakePosition = wallStake.getPosition();
      Brain.Screen.setCursor(5, 1);
      Brain.Screen.print("Current wall stake: %d", wallStakePosition);

      // Drive control
      leftDrivePower = controller1.Axis3.position(vex::percent) + controller1.Axis1.position(vex::percent);
      rightDrivePower = controller1.Axis3.position(vex::percent) - controller1.Axis1.position(vex::percent);

      leftDrive.setVelocity(leftDrivePower, vex::percent);
      rightDrive.setVelocity(rightDrivePower, vex::percent);

      // Mogo toggle
      mogoCurrentState = controller1.ButtonL2.pressing();
      helper.solenoidToggle(mogoPreviousState, mogoCurrentState, mogoNewState, mogo);

      // Intake toggle
      intakeCurrentState = controller1.ButtonLeft.pressing();
      helper.solenoidToggle(intakePreviousState, intakeCurrentState, intakeNewState, intakePiston);

      hangCurrentState = controller1.ButtonB.pressing();
      helper.solenoidToggle(hangPreviousState, hangCurrentState, hangNewState, hangHooks); 

      // Hook toggle
      hookCurrentState = controller1.ButtonR1.pressing();
      if (hookCurrentState && !hookPreviousState) {
          rightHookEngaged = !rightHookEngaged;
          
          if (rightHookEngaged) {
              ringSort.moveHooks(0);
          } else {
              ringSort.moveHooks(90);
          }
      }
      hookPreviousState = hookCurrentState;

      // Wall stake positions
      double primaryWallPosition = wallStake.getMotor1Position();
      double secondaryWallPosition = wallStake.getMotor3Position();
      Brain.Screen.setCursor(1, 1);
      Brain.Screen.print("Wall pos: %f", primaryWallPosition);
      Brain.Screen.setCursor(2, 1);
      Brain.Screen.print("2nd Wall pos: %f", secondaryWallPosition);

      // Intake control
      if (controller1.ButtonR2.pressing()) {
          intake.setVelocity(100, vex::pct);
      } else {
          intake.setVelocity(0, vex::pct);
      }

      // Button press detection for wall stake increment
      bool isButtonCurrentlyPressed = controller1.ButtonDown.pressing();
      if (isButtonCurrentlyPressed && !buttonPreviouslyPressed) {
          wallStake.incrementPosHigh();
      }
      buttonPreviouslyPressed = isButtonCurrentlyPressed;

      // X Button - High Position Increment
      if (controller1.ButtonX.pressing()) {
          if (!xButtonPreviouslyPressed) {
              wallStake.incrementPosHigh();
          }
          xButtonPreviouslyPressed = true;
      } else {
          xButtonPreviouslyPressed = false;
      }

      // Y Button - Low Position Increment
      if (controller1.ButtonY.pressing()) {
          if (!yButtonPreviouslyPressed) {
              wallStake.incrementPosLow();
          }
          yButtonPreviouslyPressed = true;
      } else {
          yButtonPreviouslyPressed = false;
      }

      if (controller1.ButtonRight.pressing()) {
        if (!ringSortButtonPreviouslyPressed) {
            wallStake.incrementPosLow();
        }
        ringSortButtonPreviouslyPressed = true;
    } else {
        ringSortButtonPreviouslyPressed = false;
    }

      vex::this_thread::sleep_for(20); // Small delay to prevent CPU overuse
  }
}


void DriveControl::PinkDriveControl() // Jon's Robot
{
   // State variables
   bool mogoPreviousState = true;
   bool mogoNewState;
   bool mogoCurrentState = false;
   bool intakePreviousState = true;
   bool intakeCurrentState = false;
   bool intakeNewState;
   bool hookPreviousState = false;
   bool hookCurrentState = false;
   bool rightHookEngaged = false;
   bool buttonPreviouslyPressed = false;
   bool xButtonPreviouslyPressed = false;
   bool yButtonPreviouslyPressed = false;
   bool ringSortButtonPreviouslyPressed = false;
   bool resetButtonPreviouslyPressed = false;
   bool hangPreviousState = true;
   bool hangNewState;
   bool hangCurrentState = false;
 
 
   // Drive power variables
   int leftDrivePower = 0;
   int rightDrivePower = 0;
   
   wallStake.setPosition(SCORE);
   Brain.Screen.clearScreen();
   
   while (true) {

    currentRing = ringSort.getRing();
    controller1.Screen.setCursor(1, 1);
    controller1.Screen.print("Current Ring: %d", currentRing);

       int wallStakePosition = wallStake.getPosition();
       Brain.Screen.setCursor(5, 1);
       Brain.Screen.print("Current wall stake: %d", wallStakePosition);
 
       int power = controller1.Axis3.position(vex::percent);
       int turn = controller1.Axis1.position(vex::percent);
      // turn = pow((turn/100),2)*100; // turn ramping
   
        // Drive control
        leftDrivePower = power + turn;
        rightDrivePower = power - turn;
 
       leftDrive.setVelocity(leftDrivePower, vex::percent);
       rightDrive.setVelocity(rightDrivePower, vex::percent);
 
       // Mogo toggle
       mogoCurrentState = controller1.ButtonL2.pressing();
       helper.solenoidToggle(mogoPreviousState, mogoCurrentState, mogoNewState, mogo);
 
       // Intake toggle
       intakeCurrentState = controller1.ButtonLeft.pressing();
       helper.solenoidToggle(intakePreviousState, intakeCurrentState, intakeNewState, intakePiston);

       hangCurrentState = controller1.ButtonB.pressing();
       helper.solenoidToggle(hangPreviousState, hangCurrentState, hangNewState, hangHooks);
 
       // Hook toggle
       if(controller1.ButtonR1.pressing()){
            ringSort.moveHooks(100);
       }
       else{
            ringSort.moveHooks(0);
       }

       hookPreviousState = hookCurrentState;
 
       // Wall stake positions
       double primaryWallPosition = wallStake.getMotor1Position();
       double secondaryWallPosition = wallStake.getMotor3Position();
       Brain.Screen.setCursor(1, 1);
       Brain.Screen.print("Wall pos: %f", primaryWallPosition);
       Brain.Screen.setCursor(2, 1);
       Brain.Screen.print("2nd Wall pos: %f", secondaryWallPosition);
 
       // Intake control
       if (controller1.ButtonR2.pressing()) {
           intake.setVelocity(100, vex::pct);
       } else {
           intake.setVelocity(0, vex::pct);
       }
 
       // Button press detection for wall stake increment
       bool isButtonCurrentlyPressed = controller1.ButtonDown.pressing();
       if (isButtonCurrentlyPressed && !buttonPreviouslyPressed) {
           wallStake.incrementPosHigh();
       }
       buttonPreviouslyPressed = isButtonCurrentlyPressed;
 
       // X Button - High Position Increment
       if (controller1.ButtonX.pressing()) {
           if (!xButtonPreviouslyPressed) {
               wallStake.incrementPosHigh();
           }
           xButtonPreviouslyPressed = true;
       } else {
           xButtonPreviouslyPressed = false;
       }
 
       // Y Button - Low Position Increment
       if (controller1.ButtonY.pressing()) {
           if (!yButtonPreviouslyPressed) {
               wallStake.incrementPosLow();
           }
           yButtonPreviouslyPressed = true;
       } else {
           yButtonPreviouslyPressed = false;
       }
 
       if (controller1.ButtonRight.pressing()) {
         if (!ringSortButtonPreviouslyPressed) {
             ringSort.incrementColor();
         }
         ringSortButtonPreviouslyPressed = true;
     } else {
         ringSortButtonPreviouslyPressed = false;
     }
 
     if (controller1.ButtonUp.pressing()) {
      if (!resetButtonPreviouslyPressed) {
          wallStake.incrementPosLow();
      }
      resetButtonPreviouslyPressed = true;
  } else {
      resetButtonPreviouslyPressed = false;
  }

       vex::this_thread::sleep_for(20); // Small delay to prevent CPU overuse
   }
}

void DriveControl::PurpleDriveControl() // Quinn's Robot
{
   // State variables
   bool mogoPreviousState = true;
   bool mogoNewState;
   bool mogoCurrentState = false;
   bool intakePreviousState = true;
   bool intakeCurrentState = false;
   bool intakeNewState;
   bool hookPreviousState = false;
   bool hookCurrentState = false;
   bool rightHookEngaged = false;
   bool buttonPreviouslyPressed = false;
   bool xButtonPreviouslyPressed = false;
   bool yButtonPreviouslyPressed = false;
   bool ringSortButtonPreviouslyPressed = false;
   bool resetButtonPreviouslyPressed = false;
   bool hangPreviousState = true;
   bool hangNewState;
   bool hangCurrentState = false;
 
 
 
   // Drive power variables
   int leftDrivePower = 0;
   int rightDrivePower = 0;
   
   wallStake.setPosition(SCORE);
   Brain.Screen.clearScreen();
   
   while (true) {

    currentRing = ringSort.getRing();
    controller1.Screen.setCursor(1, 1);
    controller1.Screen.print("Current Ring: %d", currentRing);

       int wallStakePosition = wallStake.getPosition();
       Brain.Screen.setCursor(5, 1);
       Brain.Screen.print("Current wall stake: %d", wallStakePosition);
 
    int power = controller1.Axis3.position(vex::percent);
    int turn = controller1.Axis1.position(vex::percent);
    //turn = pow((turn/100),2)*100; // turn ramping

       // Drive control
       leftDrivePower = power + turn;
       rightDrivePower = power - turn;
 
       leftDrive.setVelocity(leftDrivePower, vex::percent);
       rightDrive.setVelocity(rightDrivePower, vex::percent);
 
       // Mogo toggle
       mogoCurrentState = controller1.ButtonL2.pressing();
       helper.solenoidToggle(mogoPreviousState, mogoCurrentState, mogoNewState, mogo);
 
       // Intake toggle
       intakeCurrentState = controller1.ButtonLeft.pressing();
       helper.solenoidToggle(intakePreviousState, intakeCurrentState, intakeNewState, intakePiston);

       hangCurrentState = controller1.ButtonB.pressing();
       helper.solenoidToggle(hangPreviousState, hangCurrentState, hangNewState, hangHooks);
 
       // Hook toggle
       hookCurrentState = controller1.ButtonR1.pressing();
       if (hookCurrentState && !hookPreviousState) {
           rightHookEngaged = !rightHookEngaged;
           
           if (rightHookEngaged) {
               ringSort.moveHooks(0);
           } else {
               ringSort.moveHooks(90);
           }
       }
       hookPreviousState = hookCurrentState;
 
       // Wall stake positions
       double primaryWallPosition = wallStake.getMotor1Position();
       double secondaryWallPosition = wallStake.getMotor3Position();
       Brain.Screen.setCursor(1, 1);
       Brain.Screen.print("Wall pos: %f", primaryWallPosition);
       Brain.Screen.setCursor(2, 1);
       Brain.Screen.print("2nd Wall pos: %f", secondaryWallPosition);
 
       // Intake control
       if (controller1.ButtonR2.pressing()) {
           intake.setVelocity(100, vex::pct);
       } else {
           intake.setVelocity(0, vex::pct);
       }
 
       // Button press detection for wall stake increment
       bool isButtonCurrentlyPressed = controller1.ButtonDown.pressing();
       if (isButtonCurrentlyPressed && !buttonPreviouslyPressed) {
           wallStake.incrementPosHigh();
       }
       buttonPreviouslyPressed = isButtonCurrentlyPressed;
 
       // X Button - High Position Increment
       if (controller1.ButtonX.pressing()) {
           if (!xButtonPreviouslyPressed) {
               wallStake.incrementPosHigh();
           }
           xButtonPreviouslyPressed = true;
       } else {
           xButtonPreviouslyPressed = false;
       }
 
       // Y Button - Low Position Increment
       if (controller1.ButtonY.pressing()) {
           if (!yButtonPreviouslyPressed) {
               wallStake.incrementPosLow();
           }
           yButtonPreviouslyPressed = true;
       } else {
           yButtonPreviouslyPressed = false;
       }
 
       if (controller1.ButtonRight.pressing()) {
         if (!ringSortButtonPreviouslyPressed) {
             wallStake.incrementPosLow();
         }
         ringSortButtonPreviouslyPressed = true;
     } else {
         ringSortButtonPreviouslyPressed = false;
     }

     if (controller1.ButtonUp.pressing()) {
      if (!resetButtonPreviouslyPressed) {
          wallStake.incrementPosLow();
      }
      resetButtonPreviouslyPressed = true;
      } else {
      resetButtonPreviouslyPressed = false;
      }
 
       vex::this_thread::sleep_for(20); // Small delay to prevent CPU overuse
   }
}

void DriveControl::defaultControl(){
  TestControl();
}

void DriveControl::autonControl(){
  

}