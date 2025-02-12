#include "PLATT2\robot_config\subsystems\ringsort.h"


RingSort::RingSort(vex::brain& b) : 
brain{b},
hook1(vex::PORT4, vex::gearSetting::ratio6_1, false),
hook2(vex::PORT10, vex::gearSetting::ratio6_1, true),
hooks(hook1, hook2),
colorSensor(vex::PORT8),
sortPiston(ThreeWirePort.C)
{
    this->isToggle = false;
    desiredRing = NO_RING;
}

void RingSort::colorSort()
{
    
    hooks.spin(vex::forward, 0, vex::rpm);
    colorSensor.setLight(vex::ledState::on);
    colorSensor.setLightPower(100);
    colorSensor.objectDetectThreshold(100);
    while(true){
    sortPiston.set(false);

    vex::optical::rgbc currentRGB = colorSensor.getRgb();
    double currentR = currentRGB.red;
    double currentB = currentRGB.blue;

    brain.Screen.setCursor(7,1);
    brain.Screen.print("current red %f", currentR);
    brain.Screen.setCursor(8,1);
    brain.Screen.print("current blue %f", currentB);
    brain.Screen.setCursor(9,1);
    brain.Screen.print("Current ring: %d", desiredRing);
    if(colorSensor.isNearObject()){
    switch(desiredRing)
    {
        case RED_RING:
        {

         if(currentR > currentB)
         {
            hook1.resetPosition();
            hook2.resetPosition();

            double currentPos = hook1.position(vex::rev);

            while(currentPos < CHAIN_LIFT_ENCODER_TICKS)
            {
            if(currentPos < 2)
            {
                
            }
            sortPiston.set(true);

            currentPos = hook1.position(vex::rev);
            }
            sortPiston.set(false);
         }
         break;
        }
        case BLUE_RING:
        {
            if(currentB > currentR)
            {
            hook1.resetPosition();
            hook2.resetPosition();

            while(hook1.position(vex::rev) < CHAIN_LIFT_ENCODER_TICKS) {
                sortPiston.set(true);
            }
            sortPiston.set(false);

         }
         break;
        }
        case NO_RING:
        {
            break;
        }
    }
    }
    vex::wait(10, vex::msec);
}
}


void RingSort::liftToggle()
{
   // helper.booleanToggle(chainOld, chainNew, chainCurrent);
    if(chainCurrent)
    {
        hook1.spin(vex::forward, CHAIN_LIFT_NORMAL_SPEED, vex::percent);
        hook2.spin(vex::forward, CHAIN_LIFT_NORMAL_SPEED, vex::percent);
    
    }
    else
    {
        hook1.spin(vex::forward, 0, vex::percent);
        hook2.spin(vex::forward, 0, vex::percent);
    }
}
 
void RingSort::incrementColor()
{
    switch(desiredRing)
    {
        case NO_RING:
        {
            desiredRing = RED_RING;
            break;
        }
        case RED_RING:
        {
            desiredRing = BLUE_RING;
            break;
        }
        case BLUE_RING:
        {
            desiredRing = RED_RING;
            break;
        }
    }
}

void RingSort::setRing(RingColor desiredColor)
{
    desiredRing = desiredColor;
}

void RingSort::moveHooks(double velocity){
    hooks.setVelocity(velocity, vex::percent);
}
