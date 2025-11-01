#include <Arduino.h>
#define redPin 36
#define greenPin 39
#define bluePin 34
#define DelayTime 5
// put function declarations here:
int blinkLED(int pin, int delayTime);

void setup()
{
  // put your setup code here, to run once:
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}

void loop()
{
  // put your main code here, to run repeatedly:
  blinkLED(redPin, DelayTime);
  blinkLED(greenPin, DelayTime);
  blinkLED(bluePin, DelayTime);
}

// put function definitions here:
int blinkLED(int pin, int delayTime)
{
  for (int i = 0; i < 255; i++)
  {
    analogWrite(pin, i);
    delay(delayTime);
  }
  for (int i = 255; i >= 0; i--)
  {
    analogWrite(pin, i);
    delay(delayTime);
  }

  return 0;
}