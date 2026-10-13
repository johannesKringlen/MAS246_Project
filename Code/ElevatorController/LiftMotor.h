#include "Arduino.h"
#include "WString.h"
#include "HardwareSerial.h"
/*LiftMotor
This class controls the elevator’s vertical movement.

History:

revision  date        description
0.0.2     13.10.2026  implemented motor control with timer
0.0.1     01.10.2026  file created

*/

class LiftMotor
{
  private:
  // DC motor driver pins
  const int enablePin = 7; //
  const int refSpeedPin = 6; // PWM signal input in bipolar mode
  int deadband;

  public:

  void Begin() //legg inn i setup
  {
    TCCR4B = TCCR4B & 0b11111000 | 0x01; // set PWM frequency to 32 kHz
    pinMode(enablePin, OUTPUT);
    pinMode(refSpeedPin, OUTPUT);
  }

  void Move(int refSpeed, Encoder& encoder, int target)
  {
    String temp = "Encoder position 1 = ";
    temp += String(encoder.GetStatus());
    Serial.println(temp);

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

      temp = "Encoder position 2 = ";
      temp += String(encoder.GetStatus());
      Serial.println(temp);

    analogWrite(refSpeedPin, 128);

    delay(500);

    temp = "Encoder position 3 = ";
      temp += String(encoder.GetStatus());
      Serial.println(temp);


  }
  
   
};