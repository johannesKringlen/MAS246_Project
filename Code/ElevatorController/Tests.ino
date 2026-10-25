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

