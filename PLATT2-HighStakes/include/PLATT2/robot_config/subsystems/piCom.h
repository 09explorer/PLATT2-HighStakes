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
    HEADING = 6,
    XPOS = 7, 
    YPOS = 8,
    INTAKE = 9,
    HOOKS = 10,
    NAME = 11,
    AUTON = 12, 
    ALLIANCE = 13
    
};

enum nameLabel{

    PINK = 1,
    PURPLE = 2,
    RED = 1, 
    BLUE = 2, 
    COMP1 = 1, 
    SKILLS = 2 

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

        double heading;

        double xPos;

        double yPos;

        double intake;

        double hooks;

        double name;

        double auton;

        double alliance;

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