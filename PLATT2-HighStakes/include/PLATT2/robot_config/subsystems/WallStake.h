#ifndef WALLSTAKECONTROLLER_H
#define WALLSTAKECONTROLLER_H

#include "vex.h"
#include <atomic>
#include <cmath>

/// @brief An enumeration to represent each position for the wall stake subsystem.
enum Position
{
    SCORE = 1,
    HOME = 2,
    LOAD = 3,
    SCORE2 = 4,
    SCORELOW = 5,
    SCORELOW2 = 6,
    HANGLOCK = 7,
    CORNER = 8,
    STOW = 9
};

/// @brief A class to control the wall stake subsystem. 
/// @authors Dominic Young and Logan Wolf
class wallStakeController
{
private:
    /// @brief Ready position encoder location for stage 1 load.
    const double STAGE_1_LOAD = -0.79;
    
    /// @brief Ready position encoder location for stage 2 load.
    const double STAGE_2_LOAD = -0.2;

    /// @brief Ready position encoder location for stage 1 home.
    const double STAGE_1_HOME = 0;
    
    /// @brief Ready position encoder location for stage 2 home.
    const double STAGE_2_HOME = 0;

    /// @brief Ready position encoder location for stage 1 score.
    const double STAGE_1_SCORE = -2.51;
    
    /// @brief Ready position encoder location for stage 2 score.
    const double STAGE_2_SCORE = -1.53;

    /// @brief Ready position encoder location for stage 1 score2.
    const double STAGE_1_SCORE2 = -2.51;
    
    /// @brief Ready position encoder location for stage 2 score2.
    const double STAGE_2_SCORE2 = -2.1;

    /// @brief Ready position encoder location for stage 1 score low.
    const double STAGE_1_SCORELOW = -4.35;
    
    /// @brief Ready position encoder location for stage 2 score low.
    const double STAGE_2_SCORELOW = -1.16;

    /// @brief Ready position encoder location for stage 1 score low2.
    const double STAGE_1_SCORELOW2 = -4.5;
    
    /// @brief Ready position encoder location for stage 2 score low2.
    const double STAGE_2_SCORELOW2 = -1.42;

    /// @brief Ready position encoder location for stage 1 hang lock.
    const double STAGE_1_HANGLOCK = -2.67;
    
    /// @brief Ready position encoder location for stage 2 hang lock.
    const double STAGE_2_HANGLOCK = -0.87;

    /// @brief Ready position encoder location for stage 1 corner.
    const double STAGE_1_CORNER = -0.036;
    
    /// @brief Ready position encoder location for stage 2 corner.
    const double STAGE_2_CORNER = -1.65;

    /// @brief Ready position encoder location for stage 1 stow.
    const double STAGE_1_STOW = 0;
    
    /// @brief Ready position encoder location for stage 2 stow.
    const double STAGE_2_STOW = 0;

    /// @brief Motor for wall stake 1.
    vex::motor wallStake1;
    
    /// @brief Motor for wall stake 3.
    vex::motor wallStake3;

    /// @brief Tracks the previous position of the wall stake arm.
    Position oldPosition;

    /// @brief Atomic variable for the current position.
    std::atomic<Position> position;

public:
    /// @brief Constructs the wallStakeController class.
    wallStakeController();

    /// @brief Increments through the position presets. Calls the moveToPosition() method after changing the current value.
    void incrementPosHigh();

    /// @brief Increments through the low position presets.
    void incrementPosLow();

    /// @brief Moves the wall stake subsystem to the desired position.
    void moveToPosition();

    /// @brief Sets the position of the wall stake.
    /// @param position The desired position.
    void setPosition(Position position);

    /// @brief Gets the position of motor 1.
    /// @return The position of motor 1.
    double getMotor1Position();
    
    /// @brief Gets the position of motor 2.
    /// @return The position of motor 2.
    double getMotor2Position();
    
    /// @brief Gets the position of motor 3.
    /// @return The position of motor 3.
    double getMotor3Position();
    
    /// @brief Gets the current position.
    /// @return The current position.
    Position getPosition();

    /// @brief Moves the first stage of the wall stake.
    void moveFirstStage(double velocity);

    void stopFirstStage();

    void stopSecondStage();
    /// @brief Moves the second stage of the wall stake.
    void moveSecondStage(double velocity);
};

#endif
