#define kbd_es_es
#include "DigiKeyboard.h"

void setup() {
  DigiKeyboard.update();
  DigiKeyboard.delay(5000);
}

void loop() {
  DigiKeyboard.sendKeyStroke(KEY_T, MOD_CONTROL_LEFT | MOD_ALT_LEFT);
  delay(1000);
  DigiKeyboard.println(F("ls"));
  delay(1000);
  DigiKeyboard.println(F("whoami"));
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
