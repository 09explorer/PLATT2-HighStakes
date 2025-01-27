#ifndef ODOMETRY_H
#define ODOMETRY_H

#include <atomic>
#include "vex.h"

/// @brief A class to control and calculate the robot odometry subsystem.
/// @author Logan Wolf
class Odometry {
    
    private:
        /// @brief Constant for the number Pi.
        const double PI = M_PI;

        /// @brief Constant for the wheel circumfrence.
        const double CIRCUM = (PI*2.25);

        /// @brief Constant to easier represent the encoder units.
        const vex::rotationUnits ENCODER_UNITS = vex::rotationUnits::deg;

        vex::brain Brain;

        vex::rotation x_od;

        vex::rotation y_od;

        vex::inertial inert;

    public:
        Odometry(vex::brain& b, vex::rotation& x, vex::rotation& y, vex::inertial& i);

        /// @brief The main tracking algorothim for odometry.
        void tracking();
        
        /// @brief Current position.
        std::atomic<double> cPos[2];

        /// @brief Current heading.
        std::atomic<double> heading;

};

#endif