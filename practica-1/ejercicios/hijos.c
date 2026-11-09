#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/shm.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("Argumentos incorrectos");
        return 1;
    }

    int longitud_x = atoi(argv[1]);
    int longitud_y = atoi(argv[2]);

    size_t tamaño = (longitud_x + longitud_y) * sizeof(pid_t);
    int shmid = shmget(IPC_PRIVATE, tamaño, IPC_CREAT | 0666);
    if (shmid < 0) {
        perror("Error en memoria compartida");
        return 1;
    }

    pid_t pid = 0;
    pid_t *tabla = (pid_t *) shmat(shmid, NULL, 0);
    pid_t pid_subhijo = 1;
    int soy_superpadre = 1;
    tabla[0] = getpid(); // el superpadre es el primero

    for (int i = 0; i < longitud_x - 1 && pid == 0; i++) {
        pid = fork();
        if (pid == 0) {
            soy_superpadre = 0;
            tabla[i + 1] = getpid(); // cada hijo anota su pid en la siguiente casilla
        }
    }

    if (pid > 0) {
        wait(NULL);

        if (!soy_superpadre) {
            exit(0);
        }
    }

    if (pid == 0) {
        for (int j = 0; j < longitud_y && pid_subhijo > 0; j++) {
            pid_subhijo = fork();

            if (pid_subhijo == 0) {
                tabla[longitud_x + j] = getpid();

                printf("Soy el subhijo %d, mis padres son: ", getpid());
                for (int n = 0; n < longitud_x; n++) {
                    printf("%d%s", tabla[n], (n == longitud_x - 1) ? "" : ", ");
                }
                printf("\n");

                exit(0);
            }
        }

        for (int j = 0; j < longitud_y; j++) { // ultimo padre espera
            wait(NULL);
        }
        exit(0);
    }

    if (soy_superpadre) {
        printf("Soy el superpadre (%d): mis hijos finales son: ", getpid());
        for (int j = 0; j < longitud_y; j++) {
        printf("%d%s", tabla[longitud_x + j], (j == longitud_y - 1) ? "" : ", ");
        }
        printf("\n");

        shmdt((char *)tabla);
        shmctl(shmid, IPC_RMID, 0);
    }

    return 0;
}