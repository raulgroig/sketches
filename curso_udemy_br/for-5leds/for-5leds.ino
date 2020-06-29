
int contador;

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
  for(contador=2;contador<=6;contador++){
    digitalWrite(contador, HIGH);
    Serial.println(contador);
    delay(1000);
  }
  delay(1000);
  for(contador=6;contador>=2;contador--){
    digitalWrite(contador, LOW);
    Serial.println(contador);
    delay(1000);
  }
}
