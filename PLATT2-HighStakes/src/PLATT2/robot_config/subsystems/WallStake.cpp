#include "PLATT2/robot_config/subsystems/WallStake.h"

wallStakeController::wallStakeController() :
wallStake1(vex::PORT18, vex::gearSetting::ratio6_1, true), 
wallStake3(vex::PORT19, vex::gearSetting::ratio6_1, true)
{
    this->position = STOW;
    this->oldPosition = STOW;
    wallStake1.resetPosition();
    wallStake3.resetPosition();
    wallStake1.setStopping(vex::hold);
    wallStake3.setStopping(vex::hold);
    wallStake1.spin(vex::forward, 0, vex::rpm);
    wallStake3.spin(vex::forward, 0, vex::rpm);
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
double wallStakeController::getMotor3Position(){
    return wallStake3.position(vex::rev);
}


void wallStakeController::moveToPosition(){
    
    wallStake3.spin(vex::forward, 0, vex::rpm);
    wallStake1.spin(vex::forward, 0, vex::rpm);


    double moveVelocity = 65; // initial value
    
    while(true){
        

        if (position != oldPosition){
        
            switch ((Position)position){

                case SCORE:{ 
                    if(oldPosition == STOW){
                        wallStake1.spinToPosition(STAGE_1_SCORE, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                        vex::this_thread::sleep_for(300);
                        wallStake3.spinToPosition(STAGE_2_SCORE, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);        
                    }
                    else{
                    wallStake3.spinToPosition(STAGE_2_SCORE, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    wallStake1.spinToPosition(STAGE_1_SCORE, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                }
                    break;
                }
                case HOME:{
                   
                    wallStake3.spinToPosition(STAGE_2_HOME, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    wallStake1.spinToPosition(STAGE_1_HOME, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    
                    break;
                }

                case LOAD:{
                    
                    wallStake3.spinToPosition(STAGE_2_LOAD, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, true);
                    wallStake1.spinToPosition(STAGE_1_LOAD, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);

                    break;
                }

                case SCORE2:{

                    wallStake3.spinToPosition(STAGE_2_SCORE2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    wallStake1.spinToPosition(STAGE_1_SCORE2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);

                    break;

                }

                case SCORELOW:{

                    wallStake3.spinToPosition(STAGE_2_SCORELOW, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    wallStake1.spinToPosition(STAGE_1_SCORELOW, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);

                    break;

                }

                case SCORELOW2:{

                    wallStake3.spinToPosition(STAGE_2_SCORELOW2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    wallStake1.spinToPosition(STAGE_1_SCORELOW2, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct,false);

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
                    wallStake1.spinToPosition(STAGE_1_HANGLOCK, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    wallStake3.spinToPosition(STAGE_2_HANGLOCK, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);   

                    break;

                }

                case CORNER:{

                    wallStake3.spinToPosition(STAGE_2_CORNER, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct,false);
                    wallStake1.spinToPosition(STAGE_1_CORNER, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct,false);

                    break;

                }

                case STOW:{
                    wallStake3.spinToPosition(STAGE_2_CORNER, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);
                    wallStake1.spinToPosition(STAGE_1_CORNER, vex::rotationUnits::rev, moveVelocity, vex::velocityUnits::pct, false);

                    break;
                }

            }  
            this->oldPosition = position;
        }
        vex::this_thread::sleep_for(100);
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
            position = SCORE2;
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

void wallStakeController::moveFirstStage(double velocity)
{
    wallStake1.spin(vex::forward, velocity, vex::percent);

}

void wallStakeController::moveSecondStage(double velocity)
{
    wallStake3.spin(vex::forward, velocity, vex::percent);
}

void wallStakeController::stopFirstStage()
{
    wallStake1.stop();
}

void wallStakeController::stopSecondStage()
{
    wallStake3.stop();
}

void wallStakeController::resetPosition()
{
    const double zeroSpeed = 50;
    // Zero 1st Stage
    wallStake1.setVelocity(zeroSpeed, vex::pct);
    while(wallStake1.velocity(vex::velocityUnits::rpm) !=0){
        vex::this_thread::sleep_for(10);
    }
    wallStake1.stop();
    wallStake1.setPosition(STAGE_1_HARDSTOP, vex::rotationUnits::rev);

    // Zero 2nd Stage
    wallStake3.setVelocity(-zeroSpeed, vex::pct);
    while(wallStake3.velocity(vex::velocityUnits::rpm) !=0){
        vex::this_thread::sleep_for(10);
    }
    wallStake3.stop();
    wallStake3.resetPosition();

    // Set position to second score postion
    setPosition(SCORE2);
}