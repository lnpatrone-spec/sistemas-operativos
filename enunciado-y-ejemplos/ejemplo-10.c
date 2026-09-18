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