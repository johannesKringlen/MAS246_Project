/*
This file it's just to play with compenents until all program is in place
*/

bool _log= false;

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
  _log = log;
  if (eBtn1.isPressed) 
  {
    lcd.WriteToRow(1, "Opening door    ");
    if(_log)
    {
      Serial.println("Opening door");
    };
    doorMotor.OpenDoor(15, 4000);
    lcd.WriteToRow(1, "Door open       ");
    if(_log)
    {
      Serial.println("Door open");
    };
  }
  if (eBtn2.isPressed) 
  {
    lcd.WriteToRow(1, "Closing door    ");
    if(_log)
    {
      Serial.println("Closing door");
    };
    doorMotor.CloseDoor(15, 4000);
    lcd.WriteToRow(1, "Door closed     ");
    if(_log)
    {
      Serial.println("Door closed");
    };    
  }
}