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

        /// @brief Wether or not the clamp is enabled or disabled.
        double clamp;

        ///@brief desired wall stake mech position
        double wallStake;

        double colorSort;

        double intake;

        double hooks;

        double name;

        double auton;

        double alliance;

        double intakePiston;

        std::string writeString;
        
        std::string rawRead;

        std::string toString(double input);

        void addToWriteString(std::string label, double data);
        
        double getSubString(std::string rawRead);
    
    public: 

        /// @brief Starts the communication link between the V5 brain and the Pi.
        void startPiCom();
 
        double getValue(dataLabel);
        void   setValue(dataLabel, double);
       
     
};

#endif