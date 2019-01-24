#define kbd_es_es
#include "DigiKeyboard.h"

void setup() {
  DigiKeyboard.update();
  DigiKeyboard.delay(5000);
}

void loop() {
  DigiKeyboard.sendKeyStroke(KEY_F2, MOD_ALT_LEFT);
  delay(250);
  DigiKeyboard.println(F("leafpad"));
  delay(2000);
  DigiKeyboard.print(F("hola Arica.."));
  int i = 0;
  while(i<5){
    DigiKeyboard.print(F("."));
    delay(600);
    i=i+1;  
  }
  DigiKeyboard.println();
  DigiKeyboard.println(F("Estupido y sensual Rubber Ducky"));
  
  while (1){
    //Enciende el LED
    digitalWrite(0, HIGH);
    digitalWrite(1, HIGH);
    //Espera un segundo
    delay(1000);
    //Apaga el LED
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    //Espera un segundo
    delay(1000);    
  }
}
