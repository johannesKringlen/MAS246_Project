/*LCD
This class handles the communication to LCd display.
*/

#include "LiquidCrystal.h"
    
class LCD
{
  private:
    bool _log;
    static const int lcd_RS = 41;
    static const int lcd_EN = 40;
    static const int lcd_D4 = 37;
    static const int lcd_D5 = 36;
    static const int lcd_D6 = 35;
    static const int lcd_D7 = 34;
    static const int lcd_BackLight = 4;

    LiquidCrystal lcd;

  public:
    LCD()
        : lcd(lcd_RS, lcd_EN, lcd_D4, lcd_D5, lcd_D6, lcd_D7)
    {
    }
    
  void Begin(bool log)
  {
    _log =log;
    pinMode(lcd_BackLight, OUTPUT);    
    BackLight(1);
    lcd.begin(16,2);
    Clear();  
    if(_log == 1)
    {
      Serial.println("LCD initialized");
    }
  };

  void Clear()
  {
    lcd.clear();  
  }

  void WriteToRow(int rowNr, String text)
  {
    lcd.setCursor(0,rowNr);
    lcd.print(text);
  }

  void BackLight(bool OnOff)
  {
    digitalWrite(lcd_BackLight, OnOff);
  }
};