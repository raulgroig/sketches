#include <Servo.h>
 
// Pins
#define TRIG_PIN A0
#define ECHO_PIN A1
 
//Define all the connections maps to the L298N
#define enA 13
#define in1 12
#define in2 11
#define in3 7
#define in4 6
#define enB 5
#define servoPin 2
 
class Motor{
 
int enablePin;
int directionPin1;
int directionPin2;
 
public:
 
//Method to define the motor pins
Motor(int ENPin,int dPin1,int dPin2){
enablePin = ENPin;
directionPin1 = dPin1;
directionPin2 = dPin2;
};
 
//Method to drive the motor 0~255 driving forward. -1~-255 driving backward
void Drive(int speed){
if(speed>=0){
digitalWrite(directionPin1, LOW);
digitalWrite(directionPin2, HIGH);
}
else{
digitalWrite(directionPin1, HIGH);
digitalWrite(directionPin2, LOW);
speed = - speed;
}
analogWrite(enablePin, speed);
}
};
 
Motor leftMotor = Motor(enA, in1, in2);
Motor rightMotor = Motor(enB, in3, in4);
Servo myservo; // create servo object to control a servo
 
void motorInitiation(){
pinMode(enA, OUTPUT);
pinMode(in1, OUTPUT);
pinMode(in2, OUTPUT);
pinMode(enB, OUTPUT);
pinMode(in3, OUTPUT);
pinMode(in4, OUTPUT);
// Set initial direction and speed
digitalWrite(enA, LOW);
digitalWrite(enB, LOW);
digitalWrite(in1, LOW);
digitalWrite(in2, HIGH);
digitalWrite(in3, LOW);
digitalWrite(in4, HIGH);
}
 
//Variables--------------------------------------------------------------------------
// Anything over 400 cm (23200 us pulse) is "out of range"
const unsigned int MAX_DIST = 23200;
bool ObsticalAhead = false;
int servoPos = 90;
 
enum Directions { Forward, TurnLeft, TurnRight, TurnAround,Brake};
 
Directions nextStep = Forward;
 
unsigned long t1;
unsigned long t2;
unsigned long pulse_width;
float cm;
float inches;
 
//SETUP--------------------------------------------------------------------------
void setup() {
 
// The Trigger pin will tell the sensor to range find
pinMode(TRIG_PIN, OUTPUT);
digitalWrite(TRIG_PIN, LOW);
 
// We'll use the serial monitor to view the sensor output
Serial.begin(9600);
myservo.attach(servoPin);
motorInitiation();
Directions nextStep = Forward;
}
 
void loop() {
 
checkDistance();
checkDirection();
drive();
}
 
void checkDistance(){
 
// Hold the trigger pin high for at least 10 us
digitalWrite(TRIG_PIN, HIGH);
delayMicroseconds(10);
digitalWrite(TRIG_PIN, LOW);
 
// Wait for pulse on echo pin
while ( digitalRead(ECHO_PIN) == 0 );
 
// Measure how long the echo pin was held high (pulse width)
// Note: the micros() counter will overflow after ~70 min
t1 = micros();
while ( digitalRead(ECHO_PIN) == 1);
t2 = micros();
pulse_width = t2 - t1;
 
// Calculate distance in centimeters and inches. The constants
// are found in the datasheet, and calculated from the assumed speed
//of sound in air at sea level (~340 m/s).
cm = pulse_width / 58.0;
inches = pulse_width / 148.0;
 
// Print out results
if ( pulse_width > MAX_DIST ) {
//Serial.println("Out of range");
} else {
//Serial.print(cm);
//Serial.print(" cm \t");
//Serial.print(inches);
//Serial.println(" in");
}
 
// Wait at least 60ms before next measurement
delay(60);
 
if(cm<= 20){
ObsticalAhead = true;
Serial.println("Problem Ahead");
 
}
else{ ObsticalAhead = false;}
 
}
void checkDirection(){
Serial.println("checking direction");
if(ObsticalAhead ==true){
nextStep = Brake;
drive();
myservo.write(180); // tell servo to go to position in variable 'pos'
delay(400); // waits 15ms for the servo to reach the position
checkDistance();
if(ObsticalAhead ==false){//if left side is open
nextStep = TurnLeft;
Serial.println("Next step is TurnLeft");
myservo.write(90);//reset servo position
delay(400);
}
else{// left is blocked, now need to look at right
myservo.write(0); // tell servo to go to position in variable 'pos'
delay(800); // waits 15ms for the servo to reach the position
checkDistance();
if(ObsticalAhead ==false){//if right side is open
nextStep = TurnRight;
Serial.println("Next step is TurnRight");
myservo.write(90);//reset servo position
delay(400);
}
else{//right is blocked as well, need to turn around
nextStep = TurnAround;
myservo.write(90);//reset servo position
delay(300);
Serial.println("Next step is TurnAround");
}
}
 
}
else{nextStep = Forward;}//No obstical ahead
}
 
void drive(){
switch (nextStep){
case Forward:
leftMotor.Drive(255);
rightMotor.Drive(255);
Serial.println("Forward");
 
break;
case TurnLeft:
leftMotor.Drive(-255);
rightMotor.Drive(255);
Serial.println(" TurnLeft");
delay(400);
 
break;
case TurnRight:
leftMotor.Drive(255);
rightMotor.Drive(-255);
Serial.println(" TurnRight");
delay(400);
break;
case TurnAround:
leftMotor.Drive(255);
rightMotor.Drive(-255);
Serial.println(" TurnAround");
delay(600);
break;
 
case Brake:
leftMotor.Drive(0);
rightMotor.Drive(0);
Serial.println(" stopped");
}
 
}
