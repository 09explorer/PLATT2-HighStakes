#ifndef AUTONSELECTOR_H
#define AUTONSELECTOR_H

#include "vex.h"
#include <vector>

/// @brief A class to create and manage the brain screen menu to configure the robot
class AutonSelector{
    private:

    /// @brief Reference to the robot brain object
    vex::brain& Brain;

    vex::competition& m_Competition;

    /// @brief Constant to set the standard width of a button.
    const int BUTTON_WIDTH = 200;

    /// @brief Constant to set standard the height of a button.
    const int BUTTON_HEIGHT = 60;

    /// @brief Constant to set the corner height of the buttons
    const int ROBOT_BUTTON_STARTING_Y = 160;

    /// @brief Constant to set the corner x position of the button for Monica.
    const int LEFT_STARTING_X = 20;

    /// @brief Constant to set the corner x position of the button for Bill.
    const int RIGHT_STARTING_X = 260;

    /// @brief Constant to set the y position of the alliance color buttons
    const int ALLIANCE_STARTING_Y = 80;

    /// @brief Constant to set the y position of the skills mode button
    const int SKILLS_STARTING_Y = 20;

    /// @brief The Auton mode selected by the user.
    int m_selectedAuton = 0;

    /// @brief The alliance color selected by the user.
    int m_selectedAlliance = 0;

    /// @brief The robot selected by the user.
    int m_selectedRobot = 0;


    public:
    /// @brief Constructs a new auton selector object with the robot brain object
    /// @param b Robot brain object to pass in
    AutonSelector(vex::brain& b, vex::competition& comp);

    void drawMenu();

    void buttonListener();

    std::vector<int> getSelectedValues();
};

#endif