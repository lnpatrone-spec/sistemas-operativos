/* El programa coordina la sincronización entre dos procesos para evaluar el motivo exacto de la
finalización de un proceso hijo. Tras la creación del proceso secundario, el proceso padre detiene
temporalmente su avance hasta que el hijo termina. El proceso hijo finaliza retornando un código
de estado númerico (salvo que sea interrumpido externamente antes de tiempo). Al reanudar, el
proceso padre analiza la información de cierre recivida para distinguir e informar si el proceso
hijo finalizó de manera voluntaria reportando su valor de salida, o si fue forzado a terminar a 
causa de una señal del sistema operativo. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main ( ) {
    int estado, numero;
    
    switch(fork()) {
        case -1 : /* ERROR */
            perror("Error en fork");
            exit(1);
        case 0 : /* HIJO */
            numero = 13;
            printf("Soy el hijo y muero con %d...\n", numero);
            sleep(20);
            exit(numero);
        default : /* PADRE */
            wait(&estado);
            printf("Soy el padre. ");
        
            if ((estado & 0x7F) != 0) {
                printf("Mi hijo ha muerto con una señal.\n");
            } else {
                printf("Mi hijo ha muerto con exit(%d).\n",
                (estado>>8) & 0xFF);
            }
                exit(0);
    }
} 
