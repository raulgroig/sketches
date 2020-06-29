
int sensorPin = A0;
int ledPin = 9;
int ledPin2 = 7;
int sensorValue = 0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = analogRead(sensorPin);

  Serial.print("sensor = ");
  Serial.println(sensorValue);

  if(sensorValue < 30){
    digitalWrite(ledPin, HIGH);
    digitalWrite(ledPin2, LOW);
  } else if(sensorValue > 30 && sensorValue < 50) {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin, LOW);
  } else {
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin, LOW);
  }
  delay(2);

}
