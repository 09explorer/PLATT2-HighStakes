/*----------------------------------------------------------------------------*/
/*                                                                            */
/*    Module:       main.cpp                                                  */
/*    Author:       PLATT2 Dev Team                                           */
/*    Created:      12/8/2024, 8:43:04 PM                                     */
/*    Description:  PLATT2 High Stakes Codebase                               */
/*                                                                            */
/*----------------------------------------------------------------------------*/

#include "vex.h"
#include "PLATT2/robot_config/robot.h"
#include "PLATT2/robot_config/subsystems/piCom.h"
#include "PLATT2\robot_config\Autonselector.h"

using namespace vex;

// A global instance of competition
competition Competition;
Robot robot;
piCom& pi = robot.getPi();
wallStakeController& wallstakeControl = robot.getWall();
RingSort& ringSort = robot.getRings();
AutonSelector& menu = robot.getMenu();

/*---------------------------------------------------------------------------*/
/*                          Pre-Autonomous Functions                         */
/*                                                                           */
/*  You may want to perform some actions before the competition starts.      */
/*  Do them in the following function.  You must return from this function   */
/*  or the autonomous and usercontrol tasks will not be started.  This       */
/*  function is only called once after the V5 has been powered on and        */
/*  not every time that the robot is disabled.                               */
/*---------------------------------------------------------------------------*/

void pre_auton(void) {

  // All activities that occur before the competition starts
  // Example: clearing encoders, setting servo positions, ...
  robot.initalizeRobot();
  //auton selector 
  pi.setValue(NAME, PI_PURPLE);
  pi.setValue(ALLIANCE, PI_RED);
  pi.setValue(AUTON, SKILLS_1);

  //wall stake
  auto wallRun = [](void) {wallstakeControl.moveToPosition();};
  thread wallThread = thread(wallRun);

  //picom 
  auto comRun = [](void) {pi.startPiCom();};
  thread comThread = thread(comRun);

  //ring sort
  auto ringRun = [](void) {ringSort.colorSort();};
  thread ringThread = thread(ringRun);

  //ring sort
  auto menuRun = [](void) {menu.buttonListener();};
thread menuThread = thread(menuRun);


}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              Autonomous Task                              */
/*                                                                           */
/*  This task is used to control your robot during the autonomous phase of   */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void autonomous(void) {
  // ..........................................................................
  // Insert autonomous user code here.
  // ...........................................................................
  
  robot.runAutonControl();
}

/*---------------------------------------------------------------------------*/
/*                                                                           */
/*                              User Control Task                            */
/*                                                                           */
/*  This task is used to control your robot during the user control phase of */
/*  a VEX Competition.                                                       */
/*                                                                           */
/*  You must modify the code to add your own robot specific commands here.   */
/*---------------------------------------------------------------------------*/

void usercontrol(void) {
  robot.buildRobotConfig();
  robot.runDriveControl();
  //robot.runAutonControl();
}

//
// Main will set up the competition functions and callbacks.
//
int main() {
// Set up callbacks for autonomous and driver control periods.
  Competition.autonomous(autonomous);
  Competition.drivercontrol(usercontrol);

  // Run the pre-autonomous function.
  pre_auton();

  // Prevent main from exiting with an infinite loop.
  while (true) {
    this_thread::sleep_for(100);
  }
}
