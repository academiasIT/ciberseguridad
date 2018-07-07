
![](http://cms-site.inacap.cl/Assets/portal/img/logo-negro.png)

# Taller de Hacking Ético - Los Ángeles - Julio 2018. 

El fin de este taller práctico consiste en dar a conocer ciertas técnicas que permiten vulnerar la seguridad de serviodes/servicios. Con ello poder dotar del conocimiento necesario para que los asistentes, puedan asegurar su propia infraestructura. Este taller es desarrollado solo con fines educacionales.

Particularmente se trabajará con los siguientes recursos:

1. Un equipo capaz de correr dos máquinas virtuales.
1. 20 GB de espacio libre en Disco.
1. VirtualBox Pre-Instalado.
1. [Kali Linux](https://www.kali.org/downloads/) para su arquitectura.
1. Maquina virtual Vulnerable [Descarga](https://www.dropbox.com/s/j3r9l7kaydwsdm9/BSides-Vancouver-2018-Workshop.ova)
1. Las máquinas virtuales deben estar en una red común para poder conectarse.

El objetivo principal consiste en ganar permisos de ROOT sobre la máquina victima.

Dentro de un proceso de análisis de vulnerabilidades, es necesario seguir una metodología que permita hacer que el proceso sea repetible por ello, el ataque se separa en las fases Recolección y Enumeración, Análisis, Explotación y Documentación.

## Fase de Recolección de Información y Enumeración

Dentro de esta fase, es necesario tener en cuenta los datos de la máquina atacante como de la victima.
Desde el punto de vista del atacante es necesario conocer la IP del segmento al que está conectado
para poder revisar máquinas vulnerables.
El comando en Linux para revisar la IP es: `ifconfig`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/1-ifconfig.gif)
Una vez que ya tenemos la ip, debemos revisar nuestro entorno de red mediante
la famosa herramienta nmap.
Usamos el comando de la siguiente manera:

`# nmap 10.0.2.0/24 -T4 -sS`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/2-nmapRed.gif)

Recordar que los parámetros -T4 hacen un escaneo rápido y -sS permite identificación de servicios asociados a los puertos.
Como podemos ver en la salida del comando, se encontró la IP 10.0.2.8 con 3 puertos abiertos: 21, 22 y 80.
Como primer paso verificaremos mediante navegador qué hay detras de ese servicio http.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/3-webhttp.gif)

Luego, entramos a verificar si existen archivos interesante en el servidor http.
Esto se hace mediante el conjunto de herramientas o scripts del mismo nmap.
usaremos el comando: 

`# nmap -script http-enum 10.0.2.8`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/4-http-enum.gif)

Si miramos con atención la salida del comando, nos damos cuenta que hay un archivo denominado `robots.txt` 

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/5-robotsTxt.png)

Finalmente comprobamos la existencia de un Wordpress hosteado en la máquina victima.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/6-WordPress.png)

## Fase de Análisis
Bueno, a esta altura ya conocemos a nuestra victima, sabemos su IP `10.0.2.8` y sabemos que hostea un sitio en wordpress.
además se nos indica que está desactualizado.

Acá comenzamos a planear la estrategia y los diferentes escenarios. 
Como sabemos, wordpress es una herramienta que permite implementar blogs y sitios de manera simple. Adicionalmente permite ser extendido mediante el uso de diferentes plugins. Muchas veces esos plugins introducen brechas de seguridad al ser instalados o simplemente se usan contraseñas débiles para acceder a la administración del Wordpress.

Dentro de la distribución Kali Linux existe una herramienta denominada WPSCAN que nos permitirá auditar el sitio wordpress.
Justamente esto utilizaremos en la etapa de explotación.

## Fase de Explotación

Mediante WPSCAN procedemos a auditar el sitio worpress usando los parámetros específicos para enumerar usuarios.

`# wpscan -u 10.0.2.8/backup_wordpress --enumerate u`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/7-enumeracionUsuarios.gif)

La herramienta nos entrega dos usuarios y sus respectivas contraseñas:

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/8-UsuariosWP.png)

Intentamos loguearnos en `10.0.2.8/backup_wordpress/wp-admin` pero ninguno de los usuarios y sus respectivas contraseñas funcionan.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/9-LoginWordpress.png)

Pero como ya tenemos los usuarios, por lo cual podemos implementar un ataque de fuerza bruta. 
Nos ayudamos de la misma herramienta WPSCAN para proceder con este ataque.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/10.1-bruteforceAdmin.gif)

Acá queda de manifiesto que no existe una constraseña que nos permita ingresar con la cuenta `admin`.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/10.2-bruteforceAdmin.png)

Ahora procedemos a probar con el otro usuario `john`.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/11-password.png)

Acá si tenemos éxito logrando la clave `enigma` para el usuario `john`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/12-accesoWP.png)

Entramos al editor del tema de wordpress

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/13-EditorWP.png)

Ponemos un regalito (Shell reversa para php) en el `comments.php` y luego preparamos en la máquina atacante un listener para recibir la conexión remota.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/14-ShellReversaPhp.png)

Finalmente recibimos la conexión remota.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/15-AccesoShell.gif)

## Fase de Documentación



@agustin_salas_f
[Universidad Tecnológica de Chile INACAP](http://www.inacap.cl).
