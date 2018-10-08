
![](http://cms-site.inacap.cl/Assets/portal/img/logo-negro.png)

# Taller de Hacking con DigiSpark

EN WINDOWS INSTALAR ESTOS [DRIVERS](https://github.com/digistump/DigistumpArduino/raw/master/tools/micronucleus-2.0a4-win.zip)

Abrir el IDE Arduino como super usuario (Linux) o como Administrador (Windows), para luego entrar a:

*File -> Preferences -> Additional Boards Manager URLs*

Seguidamente ingresar la siguiente URL: `http://digistump.com/package_digistump_index.json`

La configuración debe quedar tal como se muestra en la imágen:

![](https://github.com/academiasIT/ciberseguridad/blob/master/LosAngeles/img/ide.jpg)

Luego debemos agregar la tarjeta DigiSpark, mediante el administrador del IDE.

*Tools-> Board -> Boards Manager*

Luego hacer la búsqueda por DigiStar y dar click al botón instalar.

Debería quedar como se muestra en la siguiente foto:

![](https://github.com/academiasIT/ciberseguridad/blob/master/LosAngeles/img/DigiStump%20AVR.png)

Finalmente vamos a *Tools -> Board -> Digispark (Default - 16.5mhz)*

Luego de estos simples pasos, tenemos el ambiente preparado para poder comenzar a trabajar con nuestra tarjeta.

## Ejercicio 1: Hola INACAP

```C
#define kbd_es_es
#include "DigiKeyboard.h"
 
void setup() {
  DigiKeyboard.update();
  DigiKeyboard.delay(5000);
}
 
void loop() {
  DigiKeyboard.sendKeyStroke(KEY_R, MOD_GUI_LEFT);
  delay(250);
  DigiKeyboard.println(F("notepad"));
  delay(250);
  DigiKeyboard.println(F("Hola INACAP!"));
  while(1);
}
```

## Por el premio.
## Desafío 2: calcular 2+2 :P


# ESTO ES EL FIN

Cualquier duda, me contanctan en twitter en: @agustin_salas_f

[Universidad Tecnológica de Chile INACAP](http://www.inacap.cl).

# Charla Ultra Low Cost Hacking.
https://www.youtube.com/watch?v=uXBYYiqxQOI
