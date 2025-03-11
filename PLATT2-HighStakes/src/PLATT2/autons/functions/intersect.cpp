#include "PLATT2/HelperFunctions.h"
#include "PLATT2/autons/functions.h"
#include "PLATT2/robot_config/subsystems/odometry.h"
#include <cmath>
#include <cstdlib>

double solution1[2];
double solution2[2];

double mx1;
double mx2;
double my1;
double my2;

double dx;
double dy;
double dr;
double D;

double discriminant;

double minX;
double minY;
double maxX;
double maxY;

bool sol1BetweenX;
bool sol1BetweenY;
bool sol2BetweenX;
bool sol2BetweenY;

//calculates an intersept between a line defined by the 2 input points and a circle centered around your current position. 

double* functions::intersect(double p1[2], double p2[2], double radius)
{
    static double output[2]; 
    
    //simplify field position
    double* cPos;  
    cPos = odom.getPos();

    mx1 = p1[0] - cPos[0];
    my1 = p1[1] - cPos[1];

    mx2 = p2[0] - cPos[0];
    my2 = p2[1] - cPos[1];

    //helper math
    dx = mx2 - mx1;
    dy = my2 - my1;
    dr = sqrt(pow(dx, 2) + pow(dy, 2));
    D = (mx1 * my2) - (mx2 * my1);

    discriminant = ((pow(radius, 2) * pow(dr, 2)) - pow(D, 2));

    //negitive discriminte means that there is no intersept
    if(discriminant >= 0){
       
        //calculate intersept 
        solution1[0] = (D * dy + sgn(dy) * dx * sqrt(discriminant)) / pow(dr, 2);
        solution2[0] = (D * dy - sgn(dy) * dx * sqrt(discriminant)) / pow(dr, 2);

        solution1[1] = (-1 * D * dx + (std::abs(dy)) * sqrt(discriminant)) / pow(dr, 2);
        solution2[1] = (-1 * D * dx - (std::abs(dy)) * sqrt(discriminant)) / pow(dr, 2);

        //adjust solutions to current position in field 
        solution1[0] = solution1[0] + cPos[0];
        solution1[1] = solution1[1] + cPos[1];
        solution2[0] = solution2[0] + cPos[0];
        solution2[1] = solution2[1] + cPos[1];

        //find domain and range of input line to find valid solution
        minX = fmin(p1[0], p2[0]);
        minY = fmin(p1[1], p2[1]);
        maxX = fmax(p1[0], p2[0]);
        maxY = fmax(p1[1], p2[1]);

        //logic for valid solution
        sol1BetweenX = (minX <= solution1[0]) and (solution1[0] <= maxX);
        sol1BetweenY = (minY <= solution1[1]) and (solution1[1] <= maxY);

        sol2BetweenX = (minX <= solution2[0]) and (solution2[0] <= maxX);
        sol2BetweenY = (minY <= solution2[1]) and (solution2[1] <= maxY);


        //find best solution and set it as the target
        if((sol1BetweenX and sol1BetweenY) or (sol2BetweenX and sol2BetweenY)){

            if((sol1BetweenX and sol1BetweenY) and (sol2BetweenX and sol2BetweenY)){

                if(pythag(solution1, p2) < pythag(solution2, p2)){

                    output[0] = solution1[0]; 
                    output[1] = solution1[1]; 
                    
                }else{

                    output[0] = solution2[0]; 
                    output[1] = solution2[1]; 

                }

            }else{

                if(sol1BetweenX and sol1BetweenY){

                    output[0] = solution1[0]; 
                    output[1] = solution1[1]; 

                }else {
               
                    output[0] = solution2[0]; 
                    output[1] = solution2[1]; 

                }
            }
            
            oldSolution[0] = output[0];
            oldSolution[1] = output[1];

        }else{

            output[0] = oldSolution[0];
            output[1] = oldSolution[1];

        }

    
        }else{

        output[0] = oldSolution[0];
        output[1] = oldSolution[1];

    }

    return output;

}






