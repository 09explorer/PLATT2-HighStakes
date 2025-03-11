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
    /// @brief Three-wire port for connecting sensors and other devices.
    vex::triport ThreeWirePort = vex::triport(vex::PORT22);
    
    /// @brief Motor for hook 1.
    vex::motor hook1;

    /// @brief Optical sensor for detecting ring colors.
    vex::optical colorSensor;
    
    /// @brief Digital output for controlling the sorting piston.
    vex::digital_out sortPiston;
    
    /// @brief Reference to the brain object.
    vex::brain& brain;

    /// @brief Maximum speed for the chain lift.
    const double CHAIN_LIFT_MAX_SPEED {600};
    
    /// @brief Normal speed for the chain lift.
    const double CHAIN_LIFT_NORMAL_SPEED {70};
    
    /// @brief Encoder ticks for the chain lift.
    const double CHAIN_LIFT_ENCODER_TICKS {5};
    
    /// @brief Hue value for detecting red rings.
    const double RED_RING_HUE {12};
    
    /// @brief Hue value for detecting blue rings.
    const double BLUE_RING_HUE {200};

    /// @brief Atomic boolean for toggle state.
    std::atomic<bool> isToggle;

    /// @brief Atomic boolean for current chain state.
    std::atomic<bool> chainCurrent;
    
    /// @brief Atomic boolean for old chain state.
    std::atomic<bool> chainOld;
    
    /// @brief Atomic boolean for new chain state.
    std::atomic<bool> chainNew;

    /// @brief Atomic boolean for new color state.
    std::atomic<bool> colorNew;
    
    /// @brief Atomic boolean for old color state.
    std::atomic<bool> colorOld;
    
    /// @brief Atomic boolean for current color state.
    std::atomic<bool> colorCurrent;

    /// @brief Atomic boolean for new toggle state.
    std::atomic<bool> toggleNew;
    
    /// @brief Atomic boolean for old toggle state.
    std::atomic<bool> toggleOld;
    
    /// @brief Atomic boolean for current toggle state.
    std::atomic<bool> toggleCurrent;

    public:
    /// @brief Constructs the RingSort class.
    /// @param brain Reference to a brain object.
    RingSort(vex::brain& brain);

    /// @brief The algorithm for color sorting.
    void colorSort();

    /// @brief Method that runs as a separate thread. Takes input from the controller and calls the desired method based on the input.
    void controlWatcher();

    /// @brief Helper method to toggle the chain lift on and off.
    void liftToggle();

    /// @brief Helper method to increment through the ring colors to sort.
    void incrementColor();

    /// @brief Moves the hooks at a specified velocity.
    /// @param velocity The velocity to move the hooks.
    void moveHooks(double velocity);

    /// @brief Sets the desired ring color to sort.
    /// @param desiredColor The desired ring color.
    void setRing(RingColor desiredColor);

    /// @brief Gets the current sorted ring.
    RingColor getRing();

    /// @brief The desired ring color to sort.
    RingColor desiredRing;
};

#endif