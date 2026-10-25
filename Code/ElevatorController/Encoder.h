/*Encoder
This class measures the elevator’s speed and position.
*/
const int pinEncoderChA = 20; //D20
const int pinEncoderChB = 21; //D21
volatile int encoderPos = 0;
volatile bool A_set;


class Encoder
{
private:
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
  // Initialize the encoder
  void Begin()
  {
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

  // Returns the encoder position
  int GetStatus()
  {
    return encoderPos;
  }
};