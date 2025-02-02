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
    CORNER = 8
};

/// @brief A class to control the wall stake subsystem. 
/// @authors Dominic Young and Logan Wolf
class wallStakeController
{
private:
    /**
     *  @brief Ready position encoder location for 
     */
    const double STAGE_1_LOAD = -2.6;
    const double STAGE_2_LOAD = -0.15;

    const double STAGE_1_HOME = 0;
    const double STAGE_2_HOME = 0;

    const double STAGE_1_SCORE = -1.38;
    const double STAGE_2_SCORE = -1.52;

    const double STAGE_1_SCORE2 = -1.28;
    const double STAGE_2_SCORE2 = -2;

    const double STAGE_1_SCORELOW = -0.58;
    const double STAGE_2_SCORELOW = -1.16;

    const double STAGE_1_SCORELOW2 = -0.47;
    const double STAGE_2_SCORELOW2 = -1.42;

    const double STAGE_1_HANGLOCK = -2.67;
    const double STAGE_2_HANGLOCK = -0.87;

    const double STAGE_1_CORNER = -0.036;
    const double STAGE_2_CORNER = -1.65;

    vex::motor wallStake1;
    vex::motor wallStake2;
    vex::motor wallStake3;

     /**
     * @brief Tracks the previous position of the wall stake arm.
     */
    Position oldPosition;


public:

    ///@brief Moves the wall stake arm to the desired position based on the current position.
    wallStakeController(vex::motor &wallStake1,vex::motor &wallStake2, vex::motor &wallStake3);

    /// @brief Moves the wall stake subsystem to the desired position.

    /// @brief Increments through the position presets. Calls the moveToPosition() method after changing the current value.
    void incrementPosHigh();

    void incrementPosLow();

    std::atomic<Position> position;

    /// @brief Moves the wall stake subsystem to the desired position.
    void moveToPosition();

};

#endif
