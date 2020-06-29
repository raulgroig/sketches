
int pinoLed = 13;
int pinoBotao = 2;
int estadoBotao = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(pinoLed,OUTPUT);
  pinMode(pinoBotao,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  estadoBotao = digitalRead(pinoBotao);

  if(estadoBotao == HIGH){
    digitalWrite(pinoLed,HIGH);
  } else {
    digitalWrite(pinoLed,LOW);
  }
}
