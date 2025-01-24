#include "vex.h"
#include "PLATT2/robot_config/subsystems/piCom.h"
#include <fcntl.h>
#include <unistd.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <atomic>
#include <sstream> 

vex::brain Brain;

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

    writeString = "";
    addToWriteString("n", name);
    addToWriteString("u", auton);
    addToWriteString("a", alliance);
    writeString = writeString + "/";
    
    //send the string to the pi
    write(writePort, writeString.c_str(), writeString.size());
    vex::this_thread::sleep_for(100);

    while (true){
        
        
        //create string of data to be sent
        //each data point has a single letter prefix for id and is ended by a semicolin
        //the entire write string is ended by a back slash 

        Brain.Screen.clearScreen();
        Brain.Screen.setCursor(3,1);
        Brain.Screen.print((double)flag);


        writeString = "";
        addToWriteString("f", flag);
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

        this->rightVel  = getSubString("r");
        this->leftVel   = getSubString("l");
        this->clamp     = getSubString("c");
        this->wallStake = getSubString("w");
        this->colorSort = getSubString("s");
        this->intake    = getSubString("i");
        this->hooks     = getSubString("o");

        //delay to alow other threads to run 
        //has to be located at this point in the program in order to prevent missing incoming data strings       
        vex::this_thread::sleep_for(1);

    }

}



double piCom::getValue(dataLabel dataType){

    switch(dataType){
        
        case FLAG:{
            return this->flag;
            break;
        }
        case RIGHTVEL:{
            return this->rightVel;
            break;
        }
        case LEFTVEL:{
            return this->leftVel;
            break;
        }
        case CLAMP:{
            return this->clamp;
            break;
        }
        case WALLSTAKE:{
            return this->wallStake;
            break;
        }
        case COLORSORT:{
            return this->colorSort;
            break;
        }
        case HEADING:{
            return this->heading;
            break;
        }
        case XPOS:{
            return this->xPos;
            break;
        }
        case YPOS:{
            return this->yPos;
            break;
        }
        case INTAKE:{
            return this->intake;
            break;
        }
        case HOOKS:{
            return this->hooks;
            break;
        }
        case NAME:{
            return this->name;
            break;
        }
        case AUTON:{
            return this->auton;
            break;
        }
        case ALLIANCE:{
            return this->alliance;
            break;
        }
    }
}
void piCom::setValue(dataLabel dataType, double value){

    switch(dataType){
        
        case FLAG:{
            this->flag = value;
            break;
        }
        case RIGHTVEL:{
            this->rightVel = value;
            break;
        }
        case LEFTVEL:{
            this->leftVel = value;
            break;
        }
        case CLAMP:{
            this->clamp = value;
            break;
        }
        case WALLSTAKE:{
            this->wallStake = value;
            break;
        }
        case COLORSORT:{
            this->colorSort = value;
            break;
        }
        case HEADING:{
            this->heading = value;
            break;
        }
        case XPOS:{
            this->xPos = value;
            break;
        }
        case YPOS:{
            this->yPos = value;
            break;
        }
        case INTAKE:{
            this->intake = value;
            break;
        }
        case HOOKS:{
            this->hooks = value;
            break;
        }
            case NAME:{
            this->name = value;
            break;
        }
        case AUTON:{
            this->auton = value;
            break;
        }
        case ALLIANCE:{
            this->alliance = value;
            break;
        }
    }
}

