#include "PLATT2\robot_config\robot.h"

Robot::Robot(Hal& hal):
hal{hal}
{
    robotID = NO_ROBOT;
    allianceID = NO_ALLIANCE;
    autonID = NO_AUTON;
}