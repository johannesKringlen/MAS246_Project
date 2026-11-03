
/*LiftMotor
This class controls the elevator’s vertical movement.
*/
#include "Logger.h"
#include "Arduino.h"
#include "WString.h"
#include "HardwareSerial.h"
#include "PID.h"

 
PID pid(1.0f, 0.0f, 1.0f);

class LiftMotor
{
  private:
  // DC motor driver pins
  const int enablePin = 7; //
  const int refSpeedPin = 6; // PWM signal input in bipolar mode
  int deadband;
  String _tempString;
  int targetPos = 0;

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
  void Move(Encoder& encoder, int nextFloor, int actualFloor)
  {
    int target = GetTarget(nextFloor);
    _tempString = "Encoder position 1 = ";
    _tempString += String(encoder.GetStatus());
    logMessage(_tempString);

    int tempSpeed = 128;
    int refSpeed = 128;
    int error = target - encoder.GetStatus();
    
    unsigned long actualTime = millis();
    unsigned long firstTime = actualTime;
    unsigned long timePassed = 0;
    int timeout = abs(nextFloor - actualFloor)*2000+2000;

    while (((abs(error) > 1) && ((refSpeed  >= 127) || (refSpeed <= 129))) || timePassed < timeout)
    {
      delayMicroseconds(800);
      actualTime = millis();

      tempSpeed = pid.CalculatePID(float(target), float(encoder.GetStatus()));
      
      refSpeed = toMotor(tempSpeed);
      
      //logMessage(String(refSpeed));
      //logMessage(String(tempSpeed));

      //enable or disable motors
      if (refSpeed != 0)
      {
        digitalWrite(enablePin, HIGH);
      }
      else
      {
        digitalWrite(enablePin, LOW);
      }

      analogWrite(refSpeedPin, refSpeed);

      error = target - encoder.GetStatus();

      timePassed = actualTime - firstTime;
    }


    analogWrite(refSpeedPin, 128);
    _tempString = "Encoder position 2 = ";
    _tempString += String(encoder.GetStatus());
    logMessage(_tempString); 
    
    delay(500);

    _tempString = "Encoder position 3 = ";
    _tempString += String(encoder.GetStatus());
    logMessage(_tempString); 
  }

  int toMotor(int pidOutput)
  {
    int deadbandPos = 4;
    int deadbandNeg = 4;

    int pwm=128;

    int u = constrain(pidOutput, -128, 128);
    
    if (u > 0)
    {
        pwm = 128 + deadbandPos + ((127-deadbandPos)*u/256);
    }
    if (u < 0)
    {
        pwm = 128 - deadbandNeg + (127-deadbandNeg)*u/256;
    }

    return pwm;
  }

  // Sets the encoder target position for the selected floor.
  int GetTarget(int nextFloor)
  {
    targetPos = 4096*(nextFloor-1);
    return targetPos;
  }
     
};