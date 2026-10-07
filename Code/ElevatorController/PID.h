/*PID
This call will take care of the PID control
kp is the proprortional component
ki is the integral component
kd is the derivate component

History:

revision  date        description
0.0.1     07.10.2026  file created

*/

class PID(float kp, float ki, float kd)
{
  private:
  float _kp = kp;
  float _ki = ki;
  float _kd = kd;
  float _eInt = 0;
  float _ePrevious = 0;
  float _dt = 0;
  float _lastTime = millis();

  public:
  float calculatePID(float setpoint, float actual)
  {
    float actualTime = millis()
    dt =  actualTime - lastTime;
    
    float eActual = setpoint - actual;
    float eDot = (eActual - _ePrevious)/_dt;
    _eInt = _eInt + eActual*_dt;
    _lastTime = actualTime;
    _ePrevious = eActual;
    return _kp*eActual + _ki*_eInt + _kd*eDot;
  };
};