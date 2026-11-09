#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

pid_t pid_arb;

void errores(int tipo) {
    switch (tipo) {
        case 1:
            printf("No he podido crear los procesos\n");
            exit(1);
            break;
        case 2:
            printf("Argumentos incorrectos\n");
            exit(1);
            break;
    }
}

void despertador(int s) {}

void tiempo_pasado(int s) {
    char pid_str[16];
    sprintf(pid_str, "%d", pid_arb);
            
    if (fork() == 0) {
        execlp("pstree", "pstree", "-c", "-p", pid_str, NULL);
        perror("Error al ejecutar pstree");
        exit(1);
    }
    wait(NULL);
}

void proceso_B(pid_t pid_a, int segundos) {
    int pid_b = getpid();
    pid_t pids[3];
    signal(SIGUSR1, despertador);

    printf("Soy el proceso B: mi pid es %d. Mi padre es %d. Mi abuelo es %d\n", pid_b, pid_a, pid_arb);
            
    for (int i = 0; i < 3; i++) {
        pids[i] = fork();
        if (pids[i] == -1) errores(1);

        if (pids[i] == 0) { // cada hijo
            signal(SIGUSR1, despertador);

            if (i == 0) {
                printf("Soy el proceso X: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n", getpid(), pid_b, pid_a, pid_arb);
                pause();
                printf("Soy X (%d) y muero\n", getpid());
                exit(0);
            } else if (i == 1) {
                printf("Soy el proceso Y: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n", getpid(), pid_b, pid_a, pid_arb);
                pause();
                printf("Soy Y (%d) y muero\n", getpid());
                exit(0);
            } else {
                printf("Soy el proceso Z: mi pid es %d. Mi padre es %d. Mi abuelo es %d. Mi bisabuelo es %d\n", getpid(), pid_b, pid_a, pid_arb);
                    
                signal(SIGALRM, despertador);
                alarm(segundos);
                pause();
                    
                kill(pid_a, SIGUSR1);
                    
                pause();
                printf("Soy Z (%d) y muero\n", getpid());
                exit(0);
            }
        }
    }

    pause();

    for (int i = 2; i > -1; i--) {
        kill(pids[i], SIGUSR1);
        wait(NULL);
    }

    printf("Soy B (%d) y muero\n", pid_b);
    exit(0);
}

void proceso_A(int segundos) {
    int pid_a = getpid();
    signal(SIGUSR1, tiempo_pasado);
    printf("Soy el proceso A: mi pid es %d. Mi padre es %d\n", pid_a, pid_arb);
    
    pid_t pid_hijo_b = fork();

    switch (pid_hijo_b) {
        case -1: 
            errores(1); 
            break;
        case 0: 
            proceso_B(pid_a, segundos);
            break;
        default:
            pause();
            kill(pid_hijo_b, SIGUSR1);
            wait(NULL);
            printf("Soy A (%d) y muero\n", pid_a);
            exit(0);
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) errores(2);

    pid_arb = getpid();
    int segundos = atoi(argv[1]);

    printf("Soy el proceso ejec: mi pid es %d\n", pid_arb);

    pid_t pid_hijo_a = fork();

    switch (pid_hijo_a) {
        case -1: 
            errores(1); 
            break;
        case 0: 
            proceso_A(segundos);
            break;
        default:
            wait(NULL);
            printf("Soy ejec (%d) y muero\n", pid_arb);
            break;
    }
    return 0;
}