/*
  Analog Input

  Demonstrates analog input by reading an analog sensor on analog pin 0 and
  turning on and off a light emitting diode(LED) connected to digital pin 13.
  The amount of time the LED will be on and off depends on the value obtained
  by analogRead().

  The circuit:
  - potentiometer
    center pin of the potentiometer to the analog input 0
    one side pin (either one) to ground
    the other side pin to +5V
  - LED
    anode (long leg) attached to digital output 13
    cathode (short leg) attached to ground

  - Note: because most Arduinos have a built-in LED attached to pin 13 on the
    board, the LED is optional.

  created by David Cuartielles
  modified 30 Aug 2011
  By Tom Igoe

  This example code is in the public domain.

  http://www.arduino.cc/en/Tutorial/AnalogInput
*/

const int sensorPin1 = A0;    // select the input pin for the potentiometer
const int sensorPin2 = A1;    // select the input pin for the potentiometer
const int sensorPin3 = A2;    // select the input pin for the potentiometer
const int ledPinR = 6;      // select the pin for the LED
const int ledPinG = 5;      // select the pin for the LED
const int ledPinB = 3;      // select the pin for the LED
int sensorValue1 = 0;  // variable to store the value coming from the sensor
int sensorValue2 = 0;  // variable to store the value coming from the sensor
int sensorValue3 = 0;  // variable to store the value coming from the sensor

void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(ledPinR, OUTPUT);
  pinMode(ledPinG, OUTPUT);
  pinMode(ledPinB, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // read the value from the sensor:
  sensorValue1 = map(analogRead(sensorPin1), 0, 1023, 0, 255);
  sensorValue2 = map(analogRead(sensorPin2), 0, 1023, 0, 255);
  sensorValue3 = map(analogRead(sensorPin3), 0, 1023, 0, 255);
  // turn the ledPin on
  analogWrite(ledPinR, sensorValue1);
  analogWrite(ledPinG, sensorValue2);
  analogWrite(ledPinB, sensorValue3);
}
