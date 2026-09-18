#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Argumentos incorrectos\n");
    } else {
        int filas = atoi(argv[1]);
        int columnas = atoi(argv[2]);
        int pid = 1;
        int soy_raiz = 1;
        pid_t pid_raiz = getpid();

        for (int i = 0; i < columnas && pid > 0; i++) {
            pid = fork();
            if (pid == 0) {
                soy_raiz = 0;
            }
        }

        if (!soy_raiz) {
            for (int j = 0; j < filas - 1 && pid == 0; j++) {
                pid = fork();
            }
        }

        if (soy_raiz) {
            sleep(1);

            char orden[32];
            sprintf(orden, "pstree -c %d", pid_raiz);
            system(orden);

            for (int i = 0; i < columnas; i++) {
                wait(NULL);
            }
        } else {
            if (pid > 0) {
                wait(NULL);
            } else {
                sleep(3); // sino no salen
            }
        }
    }
    return 0;
}