/*
The goal of this game is to repeat a sequence of lights and notes with 7 levels of difficulty. 
Based on the "Piezo Buzzer Sound Recall Game" example of Lee Assam from Arduino Bootcamp.
Created: 26/06/2020
Author: Raul G Roig
*/

#include <Bounce2.h>
#include "pitches.h"

//Define the LEDs pins
#define LED1 3
#define LED2 4
#define LED3 5
#define LED4 6

// Defining the buttons pins
#define BUTTON1 7
#define BUTTON2 8
#define BUTTON3 9
#define BUTTON4 10

//Defining the Buzzer pin
#define BUZZER 11

// Instantiate Bounce objects
Bounce debouncer1 = Bounce(); 
Bounce debouncer2 = Bounce(); 
Bounce debouncer3 = Bounce(); 
Bounce debouncer4 = Bounce();

//Change this variable to increase number of notes to play
//int noteSequence[4];
//int numNotes =  sizeof(noteSequence)/sizeof(int);
int noteSequence_1[3];
int noteSequence_2[4];
int noteSequence_3[5];
int noteSequence_4[6];
int noteSequence_5[7];
int noteSequence_6[8];
int noteSequence_7[9];
int numNotes =  3;
int currentNote = 0;
int lives = 3;
boolean isPlaying = false;

void setup() {

  // Start serial
  Serial.begin(9600);
  
  // Setup the buttons with an internal pull-up
  pinMode(BUTTON1, INPUT_PULLUP);
  pinMode(BUTTON2, INPUT_PULLUP);
  pinMode(BUTTON3, INPUT_PULLUP);
  pinMode(BUTTON4, INPUT_PULLUP);
  
  // Setup the Bounce instances
  debouncer1.attach(BUTTON1);
  debouncer1.interval(5); // interval in ms  
  debouncer2.attach(BUTTON2);
  debouncer2.interval(5); // interval in ms  
  debouncer3.attach(BUTTON3);
  debouncer3.interval(5); // interval in ms  
  debouncer4.attach(BUTTON4);
  debouncer4.interval(5); // interval in ms  

  // wait a little before start
  delay(2000);
  // print first sentences
  Serial.println("O jogo vai começar, boa sorte!");
  Serial.print("Fase: ");
  Serial.println(numNotes-2);
  Serial.print("Vidas: ");
  Serial.println(lives);
  
  // generating a random number
  randomSeed(analogRead(0));
  // get first sequence of notes
  generateSequence();
}

void loop() {
  
  if (!isPlaying) {
    isPlaying = true;
    currentNote = 0; 
    switch(numNotes){
      case 3:
        playSequence(noteSequence_1);
        break;
      case 4: 
        playSequence(noteSequence_2);
        break; 
      case 5: 
        playSequence(noteSequence_3);
        break; 
      case 6: 
        playSequence(noteSequence_4);
        break; 
      case 7: 
        playSequence(noteSequence_5);
        break; 
      case 8: 
        playSequence(noteSequence_6);
        break;
      case 9: 
        playSequence(noteSequence_7);
        break;  
    }
    
  }
  
  // Update the Bounce instances
  debouncer1.update();
  debouncer2.update();
  debouncer3.update();
  debouncer4.update();

  // Check the pressed buttons
  if (debouncer1.fell()){
    playButtonNote(1);
    verifyNote(1);
  }
  
  if (debouncer2.fell()){
    playButtonNote(2);
    verifyNote(2);
  }
  
  if (debouncer3.fell()){
    playButtonNote(3);
    verifyNote(3);
  }
  if (debouncer4.fell()){
    playButtonNote(4);
    verifyNote(4);
  }
}

void playSequence(int notes[]) {
  for (int i=0; i< numNotes; i++) {
    playNote(notes[i]);
  }
}

void verifyNote(int note) {
  int noteInSequence;
  switch(numNotes){
    case 3:
      noteInSequence = noteSequence_1[currentNote];
      break;
    case 4: 
      noteInSequence = noteSequence_2[currentNote];
      break;  
    case 5: 
      noteInSequence = noteSequence_3[currentNote];
      break;
    case 6: 
      noteInSequence = noteSequence_4[currentNote];
      break;
    case 7: 
      noteInSequence = noteSequence_5[currentNote];
      break;
    case 8: 
      noteInSequence = noteSequence_6[currentNote];
      break;
    case 9: 
      noteInSequence = noteSequence_7[currentNote];
      break;
  }
  if (noteInSequence == note) { //Note is correct
    currentNote++; // Go to the next note
    if (currentNote == numNotes && numNotes == 9) { // Finish all phases
      Serial.println("Você venceu, parabéns!");
      final_win();
    } else if (currentNote == numNotes){ // Finish phase
      Serial.println("Muito bem, você acertou!");
      win(); 
      Serial.print("Fase: ");
      Serial.println(numNotes-2);
      Serial.print("Vidas: ");
      Serial.println(lives);     
    }
  } else if (lives == 1){ // Note is wrong
    Serial.println("Que pena, você perdeu...");
    final_lose();
  } else {
    Serial.println("Ops, você errou.");
    lose();
    Serial.print("Fase: ");
    Serial.println(numNotes-2);
    Serial.print("Vidas: ");
    Serial.println(lives);
  }
}

void generateSequence() {
  Serial.print("Sequência:");
  for (int i = 0; i < numNotes; i ++ ) {
    int num = random(1, 5);
    Serial.print(num);
    Serial.print(", ");
    switch(numNotes){
      case 3:
        noteSequence_1[i] = num;
        break;
      case 4: 
        noteSequence_2[i] = num;
        break; 
      case 5: 
        noteSequence_3[i] = num;
        break; 
      case 6: 
        noteSequence_4[i] = num;
        break;
      case 7: 
        noteSequence_5[i] = num;
        break;
      case 8: 
        noteSequence_6[i] = num;
        break;
      case 9: 
        noteSequence_7[i] = num;
        break;
    }
  }
  Serial.println();
}

void playNote(int note) {
  int noteDuration;
  int intervalDuration;
  switch (numNotes) {
    case 3:
      noteDuration = 1500;
      intervalDuration = 700;
      break;
    case 4:
      noteDuration = 1300;
      intervalDuration = 625;
      break;
    case 5:
      noteDuration = 1100;
      intervalDuration = 550;
      break;
    case 6:
      noteDuration = 900;
      intervalDuration = 475;
      break;
    case 7:
      noteDuration = 700;
      intervalDuration = 400;
      break;
    case 8:
      noteDuration = 550;
      intervalDuration = 325;
      break;
    case 9:
      noteDuration = 400;
      intervalDuration = 250;
      break;
  }
  switch (note) {
    case 1:
      tone(BUZZER, NOTE_C3);
      digitalWrite(LED1, HIGH);
      delay(noteDuration);
      noTone(BUZZER);
      digitalWrite(LED1, LOW);
      delay (intervalDuration);
      break;
    case 2:
      tone(BUZZER, NOTE_G3);
      digitalWrite(LED2, HIGH);
      delay(noteDuration);
      noTone(BUZZER);
      digitalWrite(LED2, LOW);
      delay (intervalDuration);   
      break;
    case 3:
      tone(BUZZER, NOTE_D4);
      digitalWrite(LED3, HIGH);
      delay(noteDuration);
      noTone(BUZZER);
      digitalWrite(LED3, LOW);
      delay (intervalDuration);   
      break; 
    case 4:
      tone(BUZZER, NOTE_A4);
      digitalWrite(LED4, HIGH);
      delay(noteDuration);
      noTone(BUZZER);
      digitalWrite(LED4, LOW); 
      delay (intervalDuration); 
      break;       
  }
}

void playButtonNote(int note) {
  switch (note) {
    case 1:
      tone(BUZZER, NOTE_C3);
      digitalWrite(LED1, HIGH);
      delay(500);
      noTone(BUZZER);
      digitalWrite(LED1, LOW);
      break;
    case 2:
      tone(BUZZER, NOTE_G3);
      digitalWrite(LED2, HIGH);
      delay(500);
      noTone(BUZZER);
      digitalWrite(LED2, LOW);   
      break;
    case 3:
      tone(BUZZER, NOTE_D4);
      digitalWrite(LED3, HIGH);
      delay(500);
      noTone(BUZZER);
      digitalWrite(LED3, LOW);   
      break; 
    case 4:
      tone(BUZZER, NOTE_A4);
      digitalWrite(LED4, HIGH);
      delay(500);
      noTone(BUZZER);
      digitalWrite(LED4, LOW);    
      break;       
  }
}

void win() {
  currentNote = 0;
  isPlaying = false; 
  numNotes++;
  generateSequence();
  delay(500);

  // Classic melody used in the Arduino tone example
  // notes in the melody:
  int melody[] = {
    NOTE_C4, NOTE_G3, NOTE_G3, NOTE_A3, NOTE_G3, 0, NOTE_B3, NOTE_C4
  };
  
  // note durations: 4 = quarter note, 8 = eighth note, etc.:
  int noteDurations[] = {
    4, 8, 8, 4, 4, 4, 4, 4
  };
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 8; thisNote++) {
  
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = 1000 / noteDurations[thisNote];
    tone(BUZZER, melody[thisNote], noteDuration);
    switch(thisNote){
      case 0:
        digitalWrite(LED1, HIGH);
        break;  
      case 1:
        digitalWrite(LED2, HIGH);
        break;
      case 2:
        digitalWrite(LED3, HIGH);
        break; 
      case 3:
        digitalWrite(LED4, HIGH);
        break;  
      case 4:
        digitalWrite(LED1, LOW);
        break;  
      case 5:
        digitalWrite(LED2, LOW);
        break;
      case 6:
        digitalWrite(LED3, LOW);
        break;
      case 7:
        digitalWrite(LED4, LOW);
        break;   
    }
  
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(BUZZER);
  }
  delay(1500);
}

void lose() {
  currentNote = 0;
  lives--;
  isPlaying = false;  
  generateSequence();
  delay(500);
  
  // notes in the melody:
  int melody[] = {
    NOTE_C3, NOTE_C2, NOTE_C1
  };
  
  // note durations:
  int noteDurations[] = {
    400, 500, 800
  };
  
  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 3; thisNote++) {
  
    // note duration directly
    tone(BUZZER, melody[thisNote]);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(noteDurations[thisNote]);
    
    // stop the tone playing:
    noTone(BUZZER);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    
    // to distinguish the notes, set a minimum time between them.
    delay(200);
  }  
  delay(1500);
}

void final_win(){
  currentNote = 0;
  isPlaying = false;  
  numNotes = 3;
  lives = 3;
  generateSequence();
  delay(500);

  // Melody of "We are the champions" by Queen
  // notes in the melody:
   
  int melody[] = {
    NOTE_F3, NOTE_DS3, NOTE_F3, NOTE_DS3, NOTE_C3, NOTE_GS2, NOTE_D3, 0,
    NOTE_F3, NOTE_G3, NOTE_A4, NOTE_C4, NOTE_A4, NOTE_D3, NOTE_E3, NOTE_D3, 0, 
    NOTE_D3, NOTE_E3, NOTE_D3, NOTE_E3, NOTE_AS3,
    NOTE_AS4, NOTE_A4, NOTE_AS4, NOTE_A4, NOTE_G3,
    NOTE_A4, NOTE_F3, NOTE_AS4, NOTE_A4, NOTE_F3, NOTE_AS4,
    NOTE_GS3, NOTE_F3, NOTE_AS4, NOTE_GS3, NOTE_F3, 0,
    NOTE_DS3, NOTE_C3, NOTE_F3
  };
  
  // note durations:
  int noteDurations[] = {
    1000, 250, 250, 500, 750, 250, 1000, 1500,
    1000, 250, 250, 500, 500, 250, 250, 1500, 1500,
    750, 500, 250, 750, 750,
    750, 500, 250, 750, 750,
    750, 500, 250, 750, 500, 250,
    750, 500, 250, 750, 750, 750,
    250, 250, 3000
  };

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 42; thisNote++) {
    if(melody[thisNote] == 0){
      noTone(BUZZER);
    } else {
      tone(BUZZER, melody[thisNote]);
    }
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(noteDurations[thisNote]);

    // stop the tone playing:
    noTone(BUZZER);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    // to distinguish the notes, set a minimum time between them.
    delay(100);
  }
  delay(1500);
}

void final_lose(){
  currentNote = 0;
  numNotes = 3;
  lives = 3;
  isPlaying = false;  
  generateSequence();
  delay(500);

  // Melody of "Sonata nº2, op 35 (Marche Funebre)" by Chopin
  // notes in the melody:
  int melody[] = {
    NOTE_D2, NOTE_D2, NOTE_D2, NOTE_D2, NOTE_F2, NOTE_E2, NOTE_E2, NOTE_D2, NOTE_D2, NOTE_D2, NOTE_D2 
  };
  
  // note durations:
  int noteDurations[] = {
    1000, 750, 250, 1000, 750, 250, 750, 250, 750, 250, 1000
  };

  // iterate over the notes of the melody:
  for (int thisNote = 0; thisNote < 11; thisNote++) {
    tone(BUZZER, melody[thisNote]);
    digitalWrite(LED1, HIGH);
    digitalWrite(LED2, HIGH);
    digitalWrite(LED3, HIGH);
    digitalWrite(LED4, HIGH);
    delay(noteDurations[thisNote]);

    // stop the tone playing:
    noTone(BUZZER);
    digitalWrite(LED1, LOW);
    digitalWrite(LED2, LOW);
    digitalWrite(LED3, LOW);
    digitalWrite(LED4, LOW);
    // to distinguish the notes, set a minimum time between them.
    delay(100);
  } 
  delay(1500);
}
