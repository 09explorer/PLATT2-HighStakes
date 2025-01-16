#include "PLATT2\HelperFunctions.h"

int HelperFunctions::sgn(double num){
   
    if (num >= 0){
        return 1;
    }else
    {
        return -1;
    }
}

double HelperFunctions::pythag(double P1[2], double P2[2]){

    double X = P2[0] - P1[0];
    double Y = P2[1] - P1[1];

    double hyp = std::sqrt(pow(X,2)+pow(Y,2));

    return hyp;

}

double HelperFunctions::roundValue(double input){

    double output = std::round(input*1000) / 1000;

    return output;
}

std::string HelperFunctions::toString(double input){

    std::ostringstream s; 

    s << input; 
    std::string str = s.str(); 
    
    return str; 

}

void HelperFunctions::solenoidToggle(bool &oldState, bool &newState, bool &current, vex::digital_out &solenoid)
{		
		if ( newState == true && oldState == false) {
			
			current = !current;

            oldState = true;
			
			if (current == false){
				solenoid.set(false);
				current = false;
			}
			else{
				solenoid.set(true);
				current = true;
			}  
		}
		oldState = newState;
}

bool HelperFunctions::booleanToggle(std::atomic<bool> &oldState, std::atomic<bool> &newState, std::atomic<bool> &current)
{		
		if ( newState == true && oldState == false) {
			
			current = !current;

            oldState = true;
			
			if (current == false){
				current = false;
			}
			else{
				current = true;
			}  
		}
		oldState.exchange(newState);

    return current;
}
