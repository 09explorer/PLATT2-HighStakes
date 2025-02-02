#include "PLATT2/robot_config/subsystems/WallStake.h"

wallStakeController::wallStakeController() :
wallStake1(vex::PORT20, vex::gearSetting::ratio6_1, true), 
wallStake2(vex::PORT9, vex::gearSetting::ratio6_1, false), 
wallStake3(vex::PORT5, vex::gearSetting::ratio6_1, true)
{

}

void wallStakeController::setPosition(Position position){
    this->position = position;
}

Position wallStakeController::getPosition(){
    return this->position;
}

double wallStakeController::getMotor1Position(){
    return wallStake1.position(vex::rev);
}
double wallStakeController::getMotor2Position(){
    return wallStake2.position(vex::rev);
}
double wallStakeController::getMotor3Position(){
    return wallStake3.position(vex::rev);
}


void wallStakeController::moveToPosition(){
    
    //wallStake3.spin(vex::forward, 0, vex::rpm);
    //wallStake2.spin(vex::forward, 0, vex::rpm);
    //wallStake1.spin(vex::forward, 0, vex::rpm);


    double moveVelocity = 3000; // initial value
    
    while(true){
        

        if (position != oldPosition){
        
            switch ((Position)position){

                case SCORE:{ 
                   
                    wallStake3.spinToPosition(STAGE_2_SCORE, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake1.spinToPosition(STAGE_1_SCORE, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_SCORE, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    
                    break;
                }
                case HOME:{
                   
                    wallStake3.spinToPosition(STAGE_2_HOME, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake1.spinToPosition(STAGE_1_HOME, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_HOME, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    
                    break;
                }

                case LOAD:{
                    
                    wallStake3.spinToPosition(STAGE_2_LOAD, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    vex::wait(100, vex::msec);
                    while (std::abs(wallStake3.velocity(vex::percent))>0.1){
                        vex::wait(10, vex::msec);
                    }

                    wallStake1.spinToPosition(STAGE_1_LOAD, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_LOAD, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);

                    break;
                }

                case SCORE2:{

                    wallStake3.spinToPosition(STAGE_2_SCORE2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake1.spinToPosition(STAGE_1_SCORE2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_SCORE2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);

                    break;

                }

                case SCORELOW:{

                    wallStake3.spinToPosition(STAGE_2_SCORELOW, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake1.spinToPosition(STAGE_1_SCORELOW, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_SCORELOW, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);

                    break;

                }

                case SCORELOW2:{

                    wallStake3.spinToPosition(STAGE_2_SCORELOW2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake1.spinToPosition(STAGE_1_SCORELOW2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_SCORELOW2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);

                    break;

                }

                case HANGLOCK:{

                    //wallStake1.spinToPosition(-2, moveVelocity);
                    //wallStake2.spinToPosition(-2, moveVelocity);
                    //pros::delay(100);
                    //pros::delay(100);
                    //while (std::abs(wallStake1.get_actual_velocity())>0.1){
                    //    pros::delay(10);
                    //}
                    //wallStake3.spinToPosition(-1, moveVelocity);
                    //
                    //pros::delay(100);
                    //while (std::abs(wallStake2.get_actual_velocity())>0.1){
                    //    pros::delay(10);
                    //}
                    wallStake1.spinToPosition(STAGE_1_HANGLOCK, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_HANGLOCK, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake3.spinToPosition(STAGE_2_HANGLOCK, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);   

                    break;

                }

                case CORNER:{

                    wallStake3.spinToPosition(STAGE_2_CORNER, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake1.spinToPosition(STAGE_1_CORNER, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);
                    wallStake2.spinToPosition(STAGE_1_CORNER, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct);

                    break;

                }

            }  
            this->oldPosition = position;
        }
        vex::wait(10, vex::msec);
    }
}

void wallStakeController::incrementPosHigh()
{
    switch((Position)position){
        
        case SCORE2:
        {
            position = LOAD;
            break;
        }
        case LOAD:
        {
            position = SCORE;
            break;
        }
        case SCORE:
        {
            position = SCORE2;
            break;
        }
        case HOME:
        { 
            position = LOAD;
            break;
        }
        case SCORELOW:
        {
            position = SCORELOW2;
            break;
        }
        case SCORELOW2:
        {
            position = LOAD;
            break;
        }
        case HANGLOCK:
        {
            position = LOAD;
            break;
        }
        case CORNER:
        {
            position = LOAD;
            break;
        }



    }
}

void wallStakeController::incrementPosLow()
{
    switch((Position)position){
        
        case SCORELOW2:
        {
            position = LOAD;
            break;
        }
        case LOAD:
        {
            position = SCORELOW;
            break;
        }
        case SCORELOW:
        {
            position = SCORELOW2;
            break;
        }
        case HOME:
        {
            position = LOAD;
            break;
        }
        case SCORE:
        {
            position = SCORE2;
            break;
        }
        case SCORE2:
        {
            position = LOAD;
            break;
        }
        case HANGLOCK:
        {
            position = LOAD;
            break;
        }
        case CORNER:
        {
            position = LOAD;
            break;
        }
    }
}
