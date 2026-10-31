#include "Arduino.h"
#include "WString.h"
#include "HardwareSerial.h"
/*LiftMotor
This class controls the elevator’s vertical movement.
*/
#include "Logger.h"

class LiftMotor
{
  private:
  // DC motor driver pins
  const int enablePin = 7; //
  const int refSpeedPin = 6; // PWM signal input in bipolar mode
  int deadband;
  String _tempString;

  public:
  // Initializes the DC motor used for the lift
  void Begin() //legg inn i setup
  {
    TCCR4B = TCCR4B & 0b11111000 | 0x01; // set PWM frequency to 32 kHz
    pinMode(enablePin, OUTPUT);
    pinMode(refSpeedPin, OUTPUT);
    logMessage("Lift motor initialized"); 
  }

  // Moves the elevator to the target position
  void Move(int refSpeed, Encoder& encoder, int target)
  {
    _tempString = "Encoder position 1 = ";
    _tempString += String(encoder.GetStatus());
    logMessage(_tempString); 
    //Serial.println(_tempString);

    refSpeed = constrain(refSpeed, -100, 100);
    //enable or disable motors
    if (refSpeed != 0)
    {
      digitalWrite(enablePin, HIGH);
      if (refSpeed<0)
      {
        deadband=-4;
      }
      else
      {
        deadband= 4;
      }
    }
    else
    {
      digitalWrite(enablePin, LOW);
    }

    int pwm = 128;
    //replace alex control with PID
    while ( abs(target - encoder.GetStatus()) > 400 ) 
    {
      //Converting drive percent to PWM
      pwm= constrain(128 + deadband + refSpeed * 127/100 , 0, 255);
      analogWrite(refSpeedPin, pwm);
    }
    while ( abs(target - encoder.GetStatus()) > 200 ) 
    {
      pwm= constrain(128 + deadband + refSpeed/4 * 127/100 , 0, 255);
      analogWrite(refSpeedPin, pwm);
    }
    while ( abs(target - encoder.GetStatus()) > 0 ) 
    {
      pwm= constrain(128 + deadband + refSpeed/8 * 127/100 , 0, 255);
      analogWrite(refSpeedPin, pwm);
    }

    _tempString = "Encoder position 2 = ";
    _tempString += String(encoder.GetStatus());
    logMessage(_tempString); 
    //Serial.println(_tempString);
    analogWrite(refSpeedPin, 128);
    delay(500);

    _tempString = "Encoder position 3 = ";
    _tempString += String(encoder.GetStatus());
    logMessage(_tempString); 
    //Serial.println(_tempString);
  }
     
};