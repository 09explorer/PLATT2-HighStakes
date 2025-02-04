#ifndef HELPER_FUNCTIONS_H
#define HELPER_FUNCTIONS_H

#include "vex.h"
#include <string>
#include <atomic>
#include <cmath>
#include <sstream> 


/// @brief A class containing general use functions used across the system.
/// @authors Dominic Young & Logan Wolf
class HelperFunctions {
    public:

        /// @brief Checks the sign of a number.
        /// @author Logan Wolf
        /// @param num Number to check the sign of.
        /// @return 1 if positive, -1 if negative.
        int sgn(double);

        /// @brief Computes the pythagorean theorum on a set of numbers.
        /// @author Logan Wolf
        /// @param  P1 (X,Y) coordinates of the point P1.
        /// @param  P2 (X,Y) coordinates of the point P2.
        /// @return The hypotenuse of those values as computed using the pythagorean theorum.
        double pythag(double[2], double[2]);

        /// @brief Rounds the value of the inputted number to four decimal places.
        /// @author Logan Wolf
        /// @param input Number to round.
        /// @return Rounded number.
        double roundValue(double);

        /// @brief Takes the inputted number and converts it to a string.
        /// @author Logan Wolf
        /// @param input Number to convert to string.
        /// @return String containing converted number.
        std::string toString(double);

        /// @brief Toggles a solenoid between true and false.
        /// @author Dominic Young
        /// @param oldState The old state of the solenoid
        /// @param newState The new state of the solenoid.
        /// @param current The current state of the solenoid.
        /// @param solenoid Refrence to the solenoid to toggle.
        void solenoidToggle(bool &oldState, bool &newState, bool &current, vex::digital_out &solenoid);

        /// @brief Toggles a boolean between true and false. Meant to be used in a while(true) loop.
        /// @author Dominic Young
        /// @param oldState The old state of the boolean.
        /// @param newState The new state of the boolean
        /// @param current The current state of the boolean
        /// @return The updated current boolean.
        bool booleanToggle(std::atomic<bool> &oldState, std::atomic<bool> &newState, std::atomic<bool> &current);
};

#endif