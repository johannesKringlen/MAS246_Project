#include "Button.h"
#include "LiftMotor.h"
#include "DoorMotor.h"
#include "Brake.h"
#include "Elevator.h" 

Elevator elevator;

Button buttons;

void setup()
{
//general

Serial.begin(9600);
delay(1500);

elevator.begin();
buttons.begin();


}

void loop()
{
  if (eBtn1.GetStatus() == HIGH)
  {
    Serial.println("button 1 pressed");
  }
delay(2000);

}
