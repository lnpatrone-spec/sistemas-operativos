#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    // Comprobación de argumentos
    if (argc != 2) {
        fprintf(stderr, "Uso: %s <segundos>\n", argv[0]);
        exit(1);
    }

    int segundos = atoi(argv[1]);
    pid_t pid_ejec = getpid();

    printf("Soy el proceso ejec: mi pid es %d\n", pid_ejec);

    // Primer fork: el proceso A
    pid_t pid_a = fork();

    if (pid_a < 0) {
        perror("Error al hacer fork");
        exit(1);
    }

    if (pid_a == 0) {
        /* PROCESO A */
        printf("Soy el proceso A: mi pid es %d. Mi padre es %d\n", getpid(), getppid());

        // TODO 1: Crear proceso B (y desde B crear X, Y, Z)
        // TODO 2: Programar la captura de la señal que enviará Z para ejecutar pstree
        // TODO 3: Esperar a que muera B antes de salir

        exit(0);
    }

    /* PROCESO ejec (padre original) */
    // TODO: Esperar correctamente a que termine A antes de imprimir la muerte
    wait(NULL);

    return 0;
}