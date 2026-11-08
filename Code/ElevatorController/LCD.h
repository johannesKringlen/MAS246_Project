/*LCD
This class handles the communication to LCD display.
*/

#include "LiquidCrystal.h"
#include "Logger.h"

class LCD
{
  private:
    static const int lcd_RS = 41;
    static const int lcd_EN = 40;
    static const int lcd_D4 = 37;
    static const int lcd_D5 = 36;
    static const int lcd_D6 = 35;
    static const int lcd_D7 = 34;
    static const int lcd_BackLight = 4;
    String _tempString;
    LiquidCrystal lcd;

  public:
    LCD()
        : lcd(lcd_RS, lcd_EN, lcd_D4, lcd_D5, lcd_D6, lcd_D7)
    {
    }

  // Initializes the LCD.  
  void Begin()
  {
    pinMode(lcd_BackLight, OUTPUT);    
    BackLight(1);
    lcd.begin(16,2);
    Clear();  
    logMessage("LCD initialized"); 
  };

  // Clears the LCD.
  void Clear()
  {
    lcd.clear();  
  }

  // Writes the specified text to the selected row.
  void WriteToRow(int rowNr, String text)
  {
    lcd.setCursor(0,rowNr);
    lcd.print(text);
  }

  // Turns the backlight on or off.
  void BackLight(bool OnOff)
  {
    digitalWrite(lcd_BackLight, OnOff);
  }
};