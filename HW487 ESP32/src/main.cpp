#include <Arduino.h>
int Led = 2; // define LED pin
int buttonpin = 36; // define photo interrupter signal pin
int val; //define a numeric variable
void setup()
{
pinMode(Led, OUTPUT); // LED pin as output
pinMode(buttonpin, INPUT); //photo interrupter pin as input
}
void loop()
{
val=digitalRead(buttonpin); //read the value of the sensor
if(val == HIGH) // turn off LED when sensor is blocked
{
digitalWrite(Led,LOW);
}
else
{
digitalWrite(Led,HIGH);// turn on LED when sensor is unblocked
}
}