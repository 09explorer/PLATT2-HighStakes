#ifndef PICOM_H   
#define PICOM_H

#include <atomic>
#include <string>

/// @brief A class to communicate and control the peripheral raspberry pi.
/// @author Logan Wolf

enum dataLabel
{
    FLAG = 0,
    RIGHTVEL = 1,
    LEFTVEL = 2,
    CLAMP = 3, 
    WALLSTAKE = 4,
    COLORSORT = 5, 
    INTAKE = 6,
    HOOKS = 7,
    NAME = 8,
    AUTON = 9, 
    ALLIANCE = 10,
    INTAKEPISTON = 11
    
};

enum nameLabel{

    PI_PINK = 1,
    PI_PURPLE = 2,
    PI_RED = 1, 
    PI_BLUE = 2, 
    PI_COMP1 = 1, 
    PI_SKILLS = 2 

};

class piCom { 
    private:
        /// @brief Current status of the Pi.
        double flag;

        /// @brief Right drivetrain velocity.
        double rightVel;

        /// @brief Left drivetrain velocity.
        double leftVel;

        /// @brief Whether or not the clamp is enabled or disabled.
        double clamp;

        /// @brief Desired wall stake mech position.
        double wallStake;

        double colorSort;
        double intake;
        double hooks;
        double name;
        double auton;
        double alliance;

        double intakePiston;

        std::string writeString;
        
        /// @brief Raw read string.
        std::string rawRead;

        /// @brief Converts a double to a string.
        /// @param input The double to convert.
        /// @return The converted string.
        std::string toString(double input);

        /// @brief Adds data to the write string.
        /// @param label The label for the data.
        /// @param data The data to add.
        void addToWriteString(std::string label, double data);
        
        /// @brief Gets a substring from the raw read string.
        /// @param rawRead The raw read string.
        /// @return The extracted substring.
        double getSubString(std::string rawRead);
    
    public: 
        /// @brief Starts the communication link between the V5 brain and the Pi.
        void startPiCom();
 
        /// @brief Gets the value of a specific data label.
        /// @param label The data label.
        /// @return The value of the data label.
        double getValue(dataLabel label);
        
        /// @brief Sets the value of a specific data label.
        /// @param label The data label.
        /// @param value The value to set.
        void setValue(dataLabel label, double value);
};

#endif