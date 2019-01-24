#define kbd_es_es
#include "DigiKeyboard.h"

void setup() {
  DigiKeyboard.update();
  DigiKeyboard.delay(5000);
}

void loop() {
  delay(1000);
  DigiKeyboard.update();
  delay(100);
  DigiKeyboard.sendKeyStroke(KEY_T, MOD_CONTROL_LEFT | MOD_ALT_LEFT); //Abre la terminal
  delay(1000);
  //Escribe en la terminal comando a comando y luego ejecuta PRINTLN
  //https://avatars1.githubusercontent.com/u/31440111 
  DigiKeyboard.print(F("cd "));
  DigiKeyboard.sendKeyStroke(KEY_7, MOD_SHIFT_LEFT);
  DigiKeyboard.print(F("home"));
  DigiKeyboard.sendKeyStroke(KEY_7, MOD_SHIFT_LEFT);
  DigiKeyboard.print(F("agustin"));
  DigiKeyboard.sendKeyStroke(KEY_7, MOD_SHIFT_LEFT);
  DigiKeyboard.println(F("Desktop"));
  
  delay(500);
  DigiKeyboard.print("wget");
  DigiKeyboard.sendKeyStroke(KEY_SPACE);
  DigiKeyboard.print("avatars1.githubusercontent.com");
  DigiKeyboard.sendKeyStroke(KEY_7, MOD_SHIFT_LEFT); //Envia un /
  DigiKeyboard.print("u");
  DigiKeyboard.sendKeyStroke(KEY_7, MOD_SHIFT_LEFT); //Envia un /
  DigiKeyboard.println("31440111");
  delay(1000);
  DigiKeyboard.println("mv 31440111 Arica2018.jpeg");
  
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
