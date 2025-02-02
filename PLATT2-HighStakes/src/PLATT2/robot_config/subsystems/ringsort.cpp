#include "PLATT2\robot_config\subsystems\ringsort.h"


RingSort::RingSort(vex::brain& b) : 
brain{b},
hook1(vex::PORT4, vex::gearSetting::ratio6_1, false),
hook2(vex::PORT13, vex::gearSetting::ratio6_1, false),
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

    while(true){
    double currentHue = colorSensor.hue();
    sortPiston.set(false);
    brain.Screen.printAt(1, 1, "current hue %f", colorSensor.hue());
    switch(desiredRing)
    {
        case RED_RING:
        {
            double upperBound = RED_RING_HUE + 5;
            double lowerBound = RED_RING_HUE - 5;

         if(currentHue < upperBound && currentHue > lowerBound)
         {
            hook1.resetPosition();
            hook2.resetPosition();

            double currentPos = hook1.position(vex::rev);

            while(currentPos < CHAIN_LIFT_ENCODER_TICKS)
            {
            sortPiston.set(true);

            currentPos = hook1.position(vex::rev);
            }
            sortPiston.set(false);
         }
         break;
        }
        case BLUE_RING:
        {

            double upperBound = BLUE_RING_HUE + 5;
            double lowerBound = BLUE_RING_HUE - 5;

            if(currentHue > BLUE_RING_HUE)
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
