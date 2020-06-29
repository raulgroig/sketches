#define potpin1  0
#define potpin2  1
#define potpin3  2
#define potpin4  3

#include <Servo.h> 
 
Servo myservoBase;  // Objeto servo para controlar a base 
Servo myservoAltura; //Objeto servo para controlar a altura do braço
Servo myservoProfundidade; //Objeto servo para profundidade a altura do braço
Servo myservoGarra;  //Objeto servo para controlar a garra
 
 
int val;    // variable to read the value from the analog pin 
 
void setup() 
{ 
  //Associa cada objeto a um pino pwm
  myservoBase.attach(10);
  myservoAltura.attach(9);
  myservoProfundidade.attach(6);
  myservoGarra.attach(5);
} 
 
void loop() 
{ 
           
  val = map(analogRead(potpin1), 0, 1023, 179, 0);    
  myservoBase.write(val);                        
  
  val = map(analogRead(potpin2), 0, 1023, 0, 179);    
  myservoAltura.write(val);                
  
  val = map(analogRead(potpin3), 0, 1023, 0, 179);     
  myservoProfundidade.write(val);  

  val = map(analogRead(potpin4), 0, 1023, 0, 99);     
  myservoGarra.write(val);  
  
  delay(100);                          
} 
