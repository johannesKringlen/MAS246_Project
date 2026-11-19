#include "Arduino.h"
#include "HardwareSerial.h"
/*PID
  This class implements a PID controller.

  kp: proportional coefficient
  ki: integral coefficient
  kd: derivative coefficient
*/

class PID
{
  private:
  float _kp;
  float _ki;
  float _kd;
  float _dt;
  float _eInt = 0;
  float _ePrevious = 0;
  unsigned long  _lastTime = 0;
  bool _firstCalculation = true;
  unsigned long _actualTime = 0;

  public:
  PID(float kp, float ki, float kd)
  : _kp(kp),
  _ki(ki),
  _kd(kd)
  {
    _lastTime = millis();
  }

  // Return the calculated PID value
  float CalculatePID(float setpoint, float actual)
  {
    _actualTime = millis();
    _dt =  (_actualTime - _lastTime); // dt in milliseconds

    // Prevent division by zero during the first calculation
    if (_dt <= 0.0f)
    {
      return 0.0f;
    }

    // Calculate the error
    float error = setpoint - actual;

    // Calculate the derivate
    float eDot = 0.0f;
    if (!_firstCalculation)
    {
      eDot = (error - _ePrevious) / _dt;
    }

    // Calculate the intergral
    _eInt = _eInt + error*_dt;

    // Update values
    _lastTime = _actualTime;
    _ePrevious = error;
    _firstCalculation = false;

    int temp = _kp*error + _ki*_eInt + _kd*eDot;

    return temp;
  };
};