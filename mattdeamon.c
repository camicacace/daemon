#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <syslog.h>

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

    openlog ("firstdaemon", LOG_PID | LOG_LOCAL1, LOG_DAEMON);
    
}

int main()
{
    
    //Funcionalidad

    return EXIT_SUCCESS;
}