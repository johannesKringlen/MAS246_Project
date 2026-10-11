/*
This file it's just to play with compenents until all program is in place
*/

const int pinSW6 = 28; // sw 6
const int pinSW7 = 29; // sw 7

void initSwitches()
{
  pinMode(pinSW6, INPUT);
  pinMode(pinSW7, INPUT);
}

void LCDOnOff()
{
  if (digitalRead(pinSW6) == HIGH) 
  {
    lcd.Clear();
    lcd.BackLight(false);
  }
  if (digitalRead(pinSW7) == HIGH) 
  {
    lcd.BackLight(true);
  }
}


void testLCD()
{
  // Test LCD
  if (eBtn1.isPressed) 
  {
    lcd.BackLight(1);
  }
  if (eBtn2.isPressed) 
  {
    lcd.BackLight(0);
    lcd.Clear();
  }
  if (eBtn3.isPressed) 
  {
    lcd.WriteToRow(0, "Moving Up       ");
  }
  if (eBtn4.isPressed) 
  {
    lcd.WriteToRow(0, "Moving Down     ");
  }
}

void testDoor(bool log)
{
  // Test Door
  if (eBtn1.isPressed) 
  {
    lcd.WriteToRow(1, "Opening door    ");
    if(log)
    {
      Serial.println("Opening door");
    };
    doorMotor.OpenDoor(15, 4000);
    lcd.WriteToRow(1, "Door open       ");
    if(log)
    {
      Serial.println("Door open");
    };
  }
  if (eBtn2.isPressed) 
  {
    lcd.WriteToRow(1, "Closing door    ");
    if(log)
    {
      Serial.println("Closing door");
    };
    doorMotor.CloseDoor(15, 4000);
    lcd.WriteToRow(1, "Door closed     ");
    if(log)
    {
      Serial.println("Door closed");
    };    
  }
}