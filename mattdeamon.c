#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>

#include <time.h>

/*M4t4r
 pgrep mattdaemon -> me da el pid
 kill pid
*/

static void skeleton_daemon()
{
    pid_t pid;

    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);

    if (pid > 0)
        exit(EXIT_SUCCESS);

    if (setsid() < 0)
        exit(EXIT_FAILURE);
 
    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();

    if (pid < 0)
        exit(EXIT_FAILURE);
   
    if (pid > 0)
        exit(EXIT_SUCCESS);
   
    /* Permisos */
    umask(0);

    /* Directorio */
    chdir("/");
   
    /* Cierra todo los archivos que quedaron abiertos por el padre */
    int x;
    for (x = sysconf(_SC_OPEN_MAX); x>=0; x--)
    {
        close (x);
    }

    // Abre el archivo de log en modo de adición.
    // Si el archivo no existe, lo crea.
    int fd = open("/home/camila/Git/daemon/daemon/daemon.log", O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        // Maneja el error...
        exit(EXIT_FAILURE);
    }

    // Redirige stdout y stderr al archivo de log.
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    // No es necesario cerrar fd aquí, se cerrará cuando el proceso termine.
}

int main()
{
    // Llama a skeleton_daemon para crear el daemon
    skeleton_daemon();
   
   // Asi ya sabemos el pid
   int i = 0;
   pid_t pid = getpid();
   printf("PID: %d\n",pid);

   while(1){
    // Aquí va la funcionalidad del daemon...
    
    time_t current_time;
    time(&current_time);

    printf("Hora actual: %s", ctime(&current_time));

    fflush(stdout); // Limpia stdout y se escribe en el archivo.
    sleep(60); 
}


    return EXIT_SUCCESS;
}