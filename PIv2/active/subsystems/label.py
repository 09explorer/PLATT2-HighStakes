from enum import Enum


class label(Enum):
    
    RESET           = 0
    
    ALLIANCE        = 1
    NAME            = 2
    AUTON           = 3

    HEADING         = 4
    XPOS            = 5
    YPOS            = 6

    HEADINGOFFSET   = 7
    XPOSOFFSET      = 8
    YPOSOFFSET      = 9 

    FLAG            = 10
    RIGHTVEL        = 11
    LEFTVEL         = 12
    CLAMP           = 13
    WALLSTAKE       = 14
    COLORSORT       = 15
    INTAKE          = 16
    HOOKS           = 17   
    INTAKEPISTON    = 18

    STATUSLIGHT     = 19
    ODOMREADY       = 20