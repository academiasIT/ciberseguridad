
![](http://cms-site.inacap.cl/Assets/portal/img/logo-negro.png)

# Taller de Hacking Ético - Los Ángeles - Julio 2018. 

El fin de este taller práctico consiste en dar a conocer ciertas técnicas que permiten vulnerar la seguirdad de serviodes/servicios. Con ello poder dotar de conocimiento necesario para que los asistentes puedan asegurar su propia infraestructura.

Este taller es con fines educacionales.

Particularmente se trabajará con los siguientes recursos:

1. Un equipo capaz de correr dos máquinas virtuales.
1. 20 GB de espacio libre en Disco.
1. VirtualBox Pre-Instalado.
1. [Kali Linux](https://www.kali.org/downloads/) para su arquitectura.
1. Maquina virtual Vulnerable [Descarga](https://www.dropbox.com/s/j3r9l7kaydwsdm9/BSides-Vancouver-2018-Workshop.ova)
1. Las máquinas virtuales deben estar en una red común para poder conectarse.


Dentro de un proceso de análisis de vulnerabilidades, es necesario seguir una metodología que permita hacer que el proceso sea repetible 

## Fase de Recolección de Información y Enumeración

Dentro de esta fase, es necesario tener en cuenta los datos de la máquina atacante como de la victima.
Desde el punto de vista del atacante es necesario conocer la IP del segmento al que está conectado
para poder revisar máquinas vulnerables.
El comando en Linux para revisar la IP es ifconfig

`# ifconfig`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/1-ifconfig.gif)
Una vez que ya tenemos la ip, debemos revisar nuestro entorno de red mediante
la famosa herramienta nmap.
Usamos nmap de la siguiente manera:

`# nmap 10.0.2.0/24 -T4 -sS`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/2-nmapRed.gif)
Recordar que los parámetros -T4 hacen un escaneo rápido y -sS permite identificación de servicios asociados a los puertos.
Como podemos ver en la salida del comando, se encontró la IP 10.0.2.8 con 3 puertos abiertos: 21, 22 y 80.
Como primer paso verificaremos mediante navegador que hay detras de ese servicio http.
![](https://github.com/academiasIT/ciberseguridad/blob/master/img/3-webhttp.gif)
Luego, entramos a verificar que archivos interesante podemos encontrar en el servidor http.
Esto se hace mediante el conjunto de herramientas o scripts del mismo nmap.
usaremos el comando:

`# nmap -script http-enum 10.0.2.8`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/4-http-enum.gif)

Si miramos con atención la salida del comando, nos damos cuenta que hay un archivo denominado `robots.txt` 

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/5-robotsTxt.png)

Finalmente vemos como existe un Wordpress hosteado en la IP victima.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/6-WordPress.png)

## Fase de Análisis



## Fase de Explotación

## Fase de Documentación



@agustin_salas_f
[Universidad Tecnológica de Chile INACAP](http://www.inacap.cl).
