/* El programa coordina a un proceso padre con el cierre de su proceso hijo a través de una
notificación automática del sistema. El hijo espera 3 segundos y finaliza devolviendo un código de
salida. Mientras tanto, el proceso padre permanece a la espera hasta que recibe el aviso del término
de su hijo, momento en el que recoge su código de finalización, lo muestra por pantalla y continúa con
su flujo de trabajo. */

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int status,pid;

void finhijo(int sig) {
    pid = wait(&status);
}

int main() {
    signal(SIGCHLD,finhijo);
    if (fork()==0) {sleep(3); exit(5);}
    pause();
    printf("mi hijo ha muerto con estado %d\n",status/256);
    printf("ahora continúo con la ejecución\n");
} 
