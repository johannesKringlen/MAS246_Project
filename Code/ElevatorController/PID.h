/*PID
  This class implements a PID controller.

  kp: proportional coefficient
  ki: integral coefficient
  kd: derivative coefficient
*/

class PID()
{
  private:
  float _kp;
  float _ki;
  float _kd;
  float _eInt = 0;
  float _ePrevious = 0;
  unsigned long  _lastTime = millis();
  bool _firstCalculation = true;

  public:
  PID(float kp, float ki, float kd)
  {
    _kp = kp;
    _ki = ki;
    _kd = kd;
    _lastTime = millis();
  }

  // Return the calculated PID value
  float CalculatePID(float setpoint, float actual)
  {
    unsigned long actualTime = millis()
    float dt =  (actualTime - lastTime)/1000.0f; // dt in seconds

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
      eDot = (error - _ePrevious) / dt;
    }

    // Calculate the intergral
    _eInt = _eInt + error*dt;

    // Update values
    _lastTime = actualTime;
    _ePrevious = error;
    
    return _kp*error + _ki*_eInt + _kd*eDot;
  };
};