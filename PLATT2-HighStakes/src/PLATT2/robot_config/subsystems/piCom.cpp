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

    writeString = writeString + label + toString(data) + ";";

}

double piCom::getSubString(std::string label){

    int index = 0;
    int endIndex = 0;
    std::string subStr;

    index = rawRead.find(label);
    endIndex = rawRead.find(";", index+1);
    subStr = rawRead.substr(index+1, endIndex-(index+1));
    
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
        addToWriteString("x", this->run);
        addToWriteString("n", this->name);
        addToWriteString("u", this->auton);
        addToWriteString("a", this->alliance);
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

        this->rightVel     = getSubString("r");
        this->leftVel      = getSubString("l");
        this->clamp        = getSubString("c");
        this->wallStake    = getSubString("w");
        this->colorSort    = getSubString("s");
        this->intake       = getSubString("i");
        this->hooks        = getSubString("o");
        this->intakePiston = getSubString("p");

        //delay to alow other threads to run 
        //has to be located at this point in the program in order to prevent missing incoming data strings       
        vex::this_thread::sleep_for(1);

    }

}

double piCom::getValue(dataLabel dataType){

    switch(dataType){
        
        case RUN:{
            return this->run;
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
        case INTAKEPISTON:{
            return this->intakePiston;
            break;
        }
    }
}
void piCom::setValue(dataLabel dataType, double value){

    switch(dataType){
        
        case RUN:{
            this->run = value;
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
        case INTAKEPISTON:{
            this->intakePiston = value;
            break;
        }
    }
}

