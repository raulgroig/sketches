void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(5,OUTPUT);
  pinMode(6,OUTPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available() > 0){
    int letra = Serial.read();
    switch(letra){
      case 'a':
        digitalWrite(2, HIGH);
        delay(2000);
        break;
      case 'b':
        digitalWrite(3, HIGH);
        delay(2000);
        break;
      case 'c':
        digitalWrite(4, HIGH);
        delay(2000);
        break;
      case 'd':
        digitalWrite(5, HIGH);
        delay(2000);
        break;
      case 'e':
        digitalWrite(6, HIGH);
        delay(2000);
        break;
      default:
        digitalWrite(2, LOW);
        digitalWrite(3, LOW);
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
        digitalWrite(6, LOW);
    }
  }

}
