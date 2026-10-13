/*Encoder
This class measures the elevator’s speed and position.

History:

revision  date        description
0.0.2     13.10.2026  Implemented encoder
0.0.1     01.10.2026  File created

*/
const int pinEncoderChA = 20; //D20
const int pinEncoderChB = 21; //D21
volatile int encoderPos = 0;
volatile bool A_set;


class Encoder
{
private:
  bool _log;

  static void doSignalA()
  {
    bool currentA = digitalRead(pinEncoderChA);
    bool currentB = digitalRead(pinEncoderChB);
    if (currentB == A_set) {
      encoderPos--;
    } else {
      encoderPos++;
    }
    A_set = currentA;
  }

public:


  void Begin(bool log)
  {
    _log = log;

    pinMode(pinEncoderChA, INPUT_PULLUP);
    pinMode(pinEncoderChB, INPUT_PULLUP);
    A_set = digitalRead(pinEncoderChA);

    attachInterrupt
    (
      digitalPinToInterrupt(pinEncoderChA),
      doSignalA,
      CHANGE
    );

  }

  


  int GetStatus()
  {
    return encoderPos;
  }

};