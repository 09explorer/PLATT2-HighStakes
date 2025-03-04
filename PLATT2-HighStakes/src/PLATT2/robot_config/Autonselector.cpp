#include "PLATT2\robot_config\Autonselector.h"

AutonSelector::AutonSelector(vex::brain& b, vex::competition& comp, piCom& pi):
Brain{b},
m_Competition{comp},
m_pi{pi}
{
  this->m_selectedAlliance = 0; // no alliance
  this->m_selectedAuton = 1; // competition auton
  this->m_selectedRobot = 0; // no robot
}

std::vector<int> AutonSelector::getSelectedValues()
{
    std::vector<int> selectedValues;
    selectedValues.push_back(m_selectedAuton); // index 0
    selectedValues.push_back(m_selectedAlliance); // index 1
    selectedValues.push_back(m_selectedRobot); // index 2
    return selectedValues;
}

void AutonSelector::drawMenu()
{
    vex::color monicaColor = vex::color(253, 75, 171);
    vex::color billColor = vex::color(119, 88, 179);

    // Draw background image
    //Brain.Screen.drawImageFromFile("chloe.png", 0, 0);

    //Draw Alliance buttons
    Brain.Screen.setFillColor(vex::color::red);
    Brain.Screen.drawRectangle(LEFT_STARTING_X, ALLIANCE_STARTING_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

    Brain.Screen.setFillColor(vex::color::blue);
    Brain.Screen.drawRectangle(RIGHT_STARTING_X, ALLIANCE_STARTING_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

    // Draw Monica button
    Brain.Screen.setFillColor(monicaColor);
    Brain.Screen.drawRectangle(LEFT_STARTING_X, ROBOT_BUTTON_STARTING_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

    //Draw Bill Button
    Brain.Screen.setFillColor(billColor);
    Brain.Screen.drawRectangle(RIGHT_STARTING_X, ROBOT_BUTTON_STARTING_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

    Brain.Screen.setFillColor(vex::color::cyan);
    Brain.Screen.drawRectangle(RIGHT_STARTING_X, SKILLS_STARTING_Y, BUTTON_WIDTH, BUTTON_HEIGHT);

    Brain.Screen.render();
}

void AutonSelector::buttonListener()
{
    const int leftMonicaX = LEFT_STARTING_X;
    const int highMonicaY = ROBOT_BUTTON_STARTING_Y;
    const int rightMonicaX = LEFT_STARTING_X + BUTTON_WIDTH;
    const int lowMonicaY = ROBOT_BUTTON_STARTING_Y + BUTTON_HEIGHT;

    const int leftBillX = RIGHT_STARTING_X;
    const int rightBillX = RIGHT_STARTING_X + BUTTON_WIDTH;
    const int highBillY = ROBOT_BUTTON_STARTING_Y;
    const int lowBillY = ROBOT_BUTTON_STARTING_Y + BUTTON_HEIGHT;

    // print default lines
    Brain.Screen.setCursor(3,1);
    Brain.Screen.setPenColor(vex::color::orange);
    Brain.Screen.print("Competition Auto");
    Brain.Screen.setCursor(2,1);
    Brain.Screen.setPenColor(vex::color::orange);
    Brain.Screen.print("No Alliance");
    Brain.Screen.setCursor(1,1);
    Brain.Screen.setPenColor(vex::color::orange);
    Brain.Screen.print("No Robot");
    Brain.Screen.render();


  while(!m_Competition.isEnabled()){
  if(Brain.Screen.pressing()){
    Brain.Screen.clearLine(3);
    if((Brain.Screen.xPosition() > leftMonicaX && Brain.Screen.xPosition() < rightMonicaX) && (Brain.Screen.yPosition() >= highMonicaY && Brain.Screen.yPosition() <= lowMonicaY))
    {
      //robot.setRobotID(true);
      Brain.Screen.setCursor(2,1);
      Brain.Screen.clearLine(2);
      Brain.Screen.setPenColor(vex::color::purple);
      Brain.Screen.print("Pink");
      m_selectedRobot = 1;
    }
    else if((Brain.Screen.xPosition() >= leftBillX && Brain.Screen.xPosition() < rightBillX) && (Brain.Screen.yPosition() >= highBillY && Brain.Screen.yPosition() <= lowBillY))
    {
      //robot.setRobotID(false);
      Brain.Screen.setCursor(2,1);
      Brain.Screen.clearLine(2);
      Brain.Screen.setPenColor(vex::color(119, 88, 179));
      Brain.Screen.print("Purple");
      m_selectedRobot = 2;
    }
    else if (Brain.Screen.xPosition() >= LEFT_STARTING_X && Brain.Screen.xPosition() <= (LEFT_STARTING_X + BUTTON_WIDTH) && Brain.Screen.yPosition() >= ALLIANCE_STARTING_Y && Brain.Screen.yPosition() <= ALLIANCE_STARTING_Y + BUTTON_HEIGHT)
    {
     Brain.Screen.setCursor(1,1);
     Brain.Screen.clearLine(1);
     Brain.Screen.setPenColor(vex::color::red);
     Brain.Screen.print("Red");
     m_selectedAlliance = 1;
    }
    else if (Brain.Screen.xPosition() >= RIGHT_STARTING_X && Brain.Screen.xPosition() <= (RIGHT_STARTING_X + BUTTON_WIDTH) && Brain.Screen.yPosition() >= ALLIANCE_STARTING_Y && Brain.Screen.yPosition() <= ALLIANCE_STARTING_Y + BUTTON_HEIGHT)
    {
     Brain.Screen.setCursor(1,1);
     Brain.Screen.clearLine(1);
     Brain.Screen.setPenColor(vex::color::blue);
     Brain.Screen.print("Blue");
     m_selectedAlliance = 2;
    }
    else if (Brain.Screen.xPosition() >= RIGHT_STARTING_X && Brain.Screen.xPosition() <= (RIGHT_STARTING_X + BUTTON_WIDTH) && Brain.Screen.yPosition() >= SKILLS_STARTING_Y && Brain.Screen.yPosition() <= SKILLS_STARTING_Y + BUTTON_HEIGHT)
    {
      Brain.Screen.setCursor(3,1);
      Brain.Screen.clearLine(3);
      Brain.Screen.setPenColor(vex::color::cyan);
      m_pi.setValue(AUTON, m_selectedAuton);
      m_pi.setValue(ALLIANCE, m_selectedAlliance);
      m_pi.setValue(NAME, m_selectedRobot);
    }
  Brain.Screen.render();
  vex::this_thread::sleep_for(20);
  }
}
Brain.Screen.clearScreen();
Brain.Screen.render();
}