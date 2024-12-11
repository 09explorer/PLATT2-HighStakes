#ifndef PICOM_H   
#define PICOM_H

#include <atomic>
#include <string>

/// @brief A class to communicate and control the peripheral raspberry pi.
/// @author Logan Wolf

class piCom { 
    
    private:
        /// @brief Current status of the Pi.
        int flag;

        /// @brief Right drivetrain velocity.
        double rightVel;

        /// @brief Left drivetrain velocity.
        double leftVel;

        /// @brief Wether or not the clamp is enabled or disabled.
        int clamp;

        ///@brief desired wall stake mech position
        int wallStake;

        int colorSort;

        double heading;

        double xPos;

        double yPos;

        int intake;

        int hooks;

        std::string writeString;
        
        std::string rawRead;

        std::string toString(double input);

        void addToWriteString(std::string label, double data);
        
        double getSubString(std::string rawRead);
    
    public: 

        /// @brief Starts the communication link between the V5 brain and the Pi.
        void startPiCom();
 
        /// @brief Sets the status of the Pi link.
        /// @param status Status to set to. -1 for off, 1 for on.
        void setStatus(int flag);

        /// @brief Gets the current status of the link.
        /// @return Current status of the link.
        int  getStatus();

        void setHeading(int heading);
        double getHeading();

        void setXPos(double xPos);
        double getXPos();
        
        void setYPos(double yPos);
        double getYPos();

        void setLeftVel(double leftVel);
        double getLeftVel();

        void setRightVel(double rightVel);
        double getRightVel();   

        void setClamp(int clamp);
        int getClamp();

        void setWallStake(int wallStake);
        int getWallStake();

        void setColorSort(int colorSort);
        int getcolorSort();
        
        void setIntake(int intake);
        int getIntake();

        void setHooks(int hooks);
        int getHooks();
 
};

#endif