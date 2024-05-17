# Daemon

## Descripción
MattDaemon es un programa daemon diseñado para ejecutarse en segundo plano y loggear en un archivo daemon.log el input del teclado.

## Compilación
Para compilar el código fuente de MattDaemon, es necesario el compilador GCC. Podés compilar el programa utilizando el siguiente comando:

sudo gcc -o mattdaemon mattdaemon.c

Este comando genera un ejecutable llamado mattdaemon a partir del archivo fuente mattdaemon.c.

## Ejecución
Para ejecutar mattdaemon, también se requieren privilegios de superusuario. Puedes iniciar el daemon con el siguiente comando:

sudo ./mattdaemon

Al ejecutarse, mattdaemon comenzará a registrar todas las entradas del teclado en el archivo daemon.log.

## Registro de Logs
El archivo de log daemon.log se encuentra en el directorio donde se ejecuta el programa. Este archivo contiene todas las entradas del teclado capturadas por el daemon, proporcionando un registro detallado de la actividad del teclado.

Nota: Este software debe ser utilizado únicamente con fines educativos y de administración del sistema en entornos donde su uso esté permitido.
