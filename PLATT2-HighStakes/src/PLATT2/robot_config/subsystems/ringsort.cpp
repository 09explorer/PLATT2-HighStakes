#include "PLATT2\robot_config\subsystems\ringsort.h"


RingSort::RingSort(vex::motor &l1, vex::motor &l2, vex::optical &o, vex::digital_out &sp, vex::brain &brain) : 
lift1{l1}, lift2{l2}, colorSensor{o}, sortPiston{sp}, brain{brain}
{
    this->isToggle = false;
    desiredRing = NO_RING;
}

void RingSort::colorSort()
{
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
            lift1.resetPosition();
            lift2.resetPosition();

            double currentPos = lift1.position(vex::rev);

            while(currentPos < CHAIN_LIFT_ENCODER_TICKS)
            {
            sortPiston.set(true);

            currentPos = lift1.position(vex::rev);
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
            lift1.resetPosition();
            lift2.resetPosition();

            while(lift1.position(vex::rev) < CHAIN_LIFT_ENCODER_TICKS) {
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
        lift1.spin(vex::forward, CHAIN_LIFT_NORMAL_SPEED, vex::percent);
        lift2.spin(vex::forward, CHAIN_LIFT_NORMAL_SPEED, vex::percent);
    
    }
    else
    {
        lift1.spin(vex::forward, 0, vex::percent);
        lift2.spin(vex::forward, 0, vex::percent);
    }
}
 
void RingSort::incrementColor()
{
    switch(desiredRing)
    {
        case RED_RING:
        {
            desiredRing = BLUE_RING;
            break;
        }
        case BLUE_RING:
        {
            desiredRing = NO_RING;
            break;
        }
        case NO_RING:
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
