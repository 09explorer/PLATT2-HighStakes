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
    /**
     *  @brief Ready position encoder location for 
     */
    const double STAGE_1_LOAD = -0.776;
    const double STAGE_2_LOAD = -0.234;

    const double STAGE_1_HOME = 0;
    const double STAGE_2_HOME = 0;

    const double STAGE_1_SCORE = -4.51;
    const double STAGE_2_SCORE = -1.53;

    const double STAGE_1_SCORE2 = -4.51;
    const double STAGE_2_SCORE2 = -2;

    const double STAGE_1_SCORELOW = -6.7;
    const double STAGE_2_SCORELOW = -1.16;

    const double STAGE_1_SCORELOW2 = -7;
    const double STAGE_2_SCORELOW2 = -1.42;

    const double STAGE_1_HANGLOCK = -2.67;
    const double STAGE_2_HANGLOCK = -0.87;

    const double STAGE_1_CORNER = -0.036;
    const double STAGE_2_CORNER = -1.65;

    const double STAGE_1_STOW = -1.3;
    const double STAGE_2_STOW = 0;

    vex::motor wallStake1;
    vex::motor wallStake2;
    vex::motor wallStake3;

     /**
     * @brief Tracks the previous position of the wall stake arm.
     */
    Position oldPosition;

    std::atomic<Position> position;

public:
    wallStakeController();

    /// @brief Increments through the position presets. Calls the moveToPosition() method after changing the current value.
    void incrementPosHigh();

    void incrementPosLow();

    /// @brief Moves the wall stake subsystem to the desired position.
    void moveToPosition();

    void setPosition(Position position);

    double getMotor1Position();
    double getMotor2Position();
    double getMotor3Position();
    Position getPosition();

};

#endif
