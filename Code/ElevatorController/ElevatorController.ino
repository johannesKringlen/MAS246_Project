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

elevator.Begin();
buttons.Begin();


}

void loop()
{
  if (eBtn1.GetStatus() == HIGH)
  {
    Serial.println("button 1 pressed");
    
  }
  if (eBtn2.GetStatus() == HIGH)
  {
    Serial.println("button 2 pressed");
    lcd.BackLight(0);
    
  }
delay(2000);

}
