/* El programa crea un nuevo proceso a partir del proceso en ejecución para demostrar la concurrencia
entre un proceso padre y su proceso hijo. Cada proceso reconoce su propio identificador y el de su
contraparte, mostrando por pantalla sus datos identificativos. Ambos procesos permanecen activos durante
un intervalo de tiempo limitado (el hijo finaliza tras una breve pausa y el padre tras un periodo
algo mayor) y cada uno notifica el término de su ejecución antes de concluir. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
 pid_t pid;
 pid = fork();
 
switch (pid) {
 case -1:
    printf ("No he podido crear el proceso hijo \n");
    break;
 case 0: 
    printf ("Soy el hijo, mi PID es %d y mi PPID es %d \n",
    getpid(), getppid());
    sleep (20);
    break;
 default:
    printf ("Soy el padre, mi PID es %d y el PID de mi hijo es %d \n",
    getpid(), pid);
    sleep (30);
 }
    printf ("Final de ejecución de %d \n", getpid());
    exit (0);
} 
