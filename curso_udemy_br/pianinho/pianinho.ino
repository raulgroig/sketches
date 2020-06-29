
//define notas
int DO = 262;
int RE = 294;
int MI = 329;
//int FA = 349;
int SOL = 392;
int LA = 440;
//int SI = 494;

int notas[5] = {DO,RE,MI,SOL,LA};

void setup() {
  // put your setup code here, to run once:
  for(int i=2; i<7; i++){
    pinMode(i,INPUT);
  }
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=2; i<7; i++){
    while(digitalRead(i) != HIGH){
      tone(12, notas[i-2]);
    }
    noTone(12);
  }

}
