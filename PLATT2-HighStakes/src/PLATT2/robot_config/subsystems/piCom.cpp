#include "vex.h"
#include "PLATT2/robot_config/subsystems/piCom.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <atomic>
#include <sstream> 

std::string piCom::toString(double input){

    std::ostringstream s; 

    s << input; 
    std::string str = s.str(); 
    
    return str; 

}

void piCom::addToWriteString(std::string label, double data){

    writeString = writeString + label + ":" + toString(data) + ";";

}

double piCom::getSubString(std::string label){

    int index = 0;
    int endIndex = 0;
    std::string subStr;

    index = rawRead.find(label+":");
    endIndex = rawRead.find(";", index+1);
    subStr = rawRead.substr(index+2, endIndex-(index+2));
    
    return strtod(subStr.c_str(), NULL);

}

void piCom::startPiCom(){

    int writePort = open("/dev/serial0", O_RDWR | O_NOCTTY | O_SYNC);   
    int readPort  = open("/dev/serial1", O_RDWR | O_NOCTTY | O_SYNC | O_NONBLOCK);

    int byteRead = 0;
    char buf[1];
    
    while (true){
        
        
        //create string of data to be sent
        //each data point has a single letter prefix for id and is ended by a semicolin
        //the entire write string is ended by a back slash 

        writeString = "";
        addToWriteString("s", flag);
        addToWriteString("h", heading);
        addToWriteString("x", xPos);
        addToWriteString("y", yPos);
        writeString = writeString + "/";
        
        //send the string to the pi
        write(writePort, writeString.c_str(), writeString.size());
        
        //Read section 

        rawRead = "";

        //waits for a bite and appends it to a string 
        //does this until a backslash is found in the string indicating the end of the sent data 
        while(byteRead>0 or rawRead.length() == 0){
           
            buf[0] = (char) 0;
            
            byteRead = read(readPort, buf, 1);
            rawRead.push_back(buf[0]);
            if (rawRead.find("/") != -1){break;}

        }
        
        //picks apart the read string to find the id characters and the data that they indicate

        rightVel = getSubString("r");
        leftVel = getSubString("l");
        clamp = getSubString("c");
        wallStake = getSubString("w");

        //delay to alow other threads to run 
        //has to be located at this point in the program in order to prevent missing incoming data strings       
        vex::this_thread::sleep_for(1);

    }

}

void piCom::setStatus(int flag){
    this->flag = flag;
}
int piCom::getStatus(){
    return this->flag;
}

void piCom::setHeading(int heading){
    this->heading = heading;
}
double piCom::getHeading(){
    return this->heading;
}

void piCom::setXPos(double xPos){
    this->xPos = xPos;
}
double piCom::getXPos(){
    return this->xPos;
}

void piCom::setYPos(double yPos){
    this->yPos = yPos;
}
double piCom::getYPos(){
    return this->yPos;
}

void piCom::setLeftVel(double leftVel){
    this->leftVel = leftVel;
}
double piCom::getLeftVel(){
    return this->leftVel;
}

void piCom::setRightVel(double rightVel){
    this->rightVel = rightVel;
}
double piCom::getLeftVel(){
    return this->rightVel;
}

void piCom::setWallStake(int wallStake){
    this->wallStake = wallStake;
}
int piCom::getWallStake(){
    return this->wallStake;
}

void piCom::setClamp(int clamp){
    this->clamp = clamp;
}
int piCom::getClamp(){
    return this->clamp;
}

void piCom::setColorSort(int colorSort){
    this->colorSort = colorSort;
}
int piCom::getcolorSort(){
    return this->colorSort;
}

void piCom::setIntake(int intake){
    this->intake = intake;
}
int piCom::getIntake(){
    return this->intake;
}

void piCom::setHooks(int hooks){
    this->hooks = hooks;
}
int piCom::getHooks(){
    return this->hooks;
}


