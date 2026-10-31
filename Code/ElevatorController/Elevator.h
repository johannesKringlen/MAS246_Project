/*Elevator
This class represents the elevator’s current state, including its floor, direction, and movement status.
*/

#include "LCD.h"
#include "Logger.h"

LCD lcd;

class Elevator
{
  private:
  
  public:
  int currentFloor; // 1 to 4
  int actualDirection; // 1 = up,  2 = down
  int lastDirection; // 1 = up,  2 = down
  bool isMoving;

  // Initializes the elevator
  void Begin()
  {
    /*Starting at floor 1 
      with door closed
      not moving */ 
    currentFloor = 1; 
    actualDirection = 1; 
    lastDirection = 2;
    isMoving = false;
    logMessage("Elevator Initialized");
    lcd.Begin();
  };
};