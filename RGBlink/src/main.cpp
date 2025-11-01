#include <Arduino.h>
#define redPin 13
#define greenPin 12
#define bluePin 11
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
  blinkLED(redPin, 5);
  blinkLED(greenPin, 5);
  blinkLED(bluePin, 5);
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