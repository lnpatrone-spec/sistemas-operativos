#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

main (int argc, char *argv[]) {
    int pid = 1; 

    int filas = atoi(argv[1]);
    int columnas = atoi(argv[2]);

    for (int i = 0; i < (columnas) && pid > 0; i++) {
        pid = fork();
    }

    if (pid == 0) {
        for (int j = 0; j < (filas - 1) && pid == 0; j++) {
            pid = fork();
        }
    }
    return 0;
} 