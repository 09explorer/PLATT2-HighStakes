#ifndef RINGSORT_H
#define RINGSORT_H

#include "vex.h"
#include <atomic>

/// @brief Enumerations for each ring. Includes an enumeration for no ring.
enum RingColor
{
    RED_RING = 1,
    BLUE_RING = 2,
    NO_RING = 3
};

/// @brief A class to control the operations relating to ring sort.
/// @author Dominic Young
class RingSort
{
    private:
    vex::motor lift1;
    vex::motor lift2;
    vex::optical colorSensor;
    vex::digital_out sortPiston;
    vex::brain brain;

    const double CHAIN_LIFT_MAX_SPEED {600};
    const double CHAIN_LIFT_NORMAL_SPEED {600};
    const double CHAIN_LIFT_ENCODER_TICKS {5};
    const double RED_RING_HUE {12};
    const double BLUE_RING_HUE {200};

    std::atomic<bool> isToggle;

    std::atomic<bool> chainCurrent;
    std::atomic<bool> chainOld;
    std::atomic<bool> chainNew;

    std::atomic<bool> colorNew;
    std::atomic<bool> colorOld;
    std::atomic<bool> colorCurrent;

    std::atomic<bool> toggleNew;
    std::atomic<bool> toggleOld;
    std::atomic<bool> toggleCurrent;



    public:
    /// @brief Constructs the RingSort class.
    /// @param l1 Refrence to lift motor #1.
    /// @param l2 Refrence to lift motor #2.
    /// @param o Refrence to optical sensor.
    /// @param sp Refrence to the solenoid for the sorting piston.
    RingSort(vex::motor &l1, vex::motor &l2, vex::optical &o, vex::digital_out &sp, vex::brain &brain);

    /// @brief The algorighim for color sorting.
    void colorSort();

    /// @brief Method that runs as a seperate thread. Takes input from the controller and calls the desired method based on the input.
    void controlWatcher();

    /// @brief Helper method to toggle the chain lift on and off.
    void liftToggle();

    /// @brief Helper method to increment through the ring colors to sort.
    void incrementColor();

    void setRing(RingColor desiredColor);

        RingColor desiredRing;
};

/// @brief Extern to the global ringController object.
extern RingSort ringController;

#endif