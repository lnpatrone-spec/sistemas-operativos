/* El programa gestiona el ciclo de vida completo de un espacio de memoria compartida en el sistema.
Primero reserva una zona de memoria común accesible por otros procesos y la prepara inicializando su
valor a cero. Tras comprobar su disponibilidad mostrando el valor almacenado, el programa desconeta
dicha zona de memoria de su espacio de trabajo y solicita al sistema operativo su eliminación
definitiva para liberar los recursos. */

#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int shmid;
int *numero = NULL;

int creaComp(void)
{
    if ((shmid = shmget(IPC_PRIVATE, sizeof(int), IPC_CREAT | 0666)) == -1)
    {
        perror("Error al crear memoria compartida: ");
        return 1;
    }

    /* vinculamos el segmento de memoria compartida al proceso */
    numero = (int *) shmat(shmid, 0, 0);

    /*iniciamos las variables */

    *numero = 0;
    return 0;
} 

void borraComp(void)
{
    char error[100];
    if (numero != NULL)
    {
        /* desvinculamos del proceso la memoria compartida */
        if (shmdt((char *)numero) < 0)
        {
            sprintf(error, "Pid %d: Error al desligar la memoria compartida:\n", getpid());
            perror(error);
            exit(3);
        }
        /* borramos la memoria compartida */
        if (shmctl(shmid, IPC_RMID, 0) < 0)
        {
            sprintf(error, "Pid %d: Error al borrar memoria compartida:\n", getpid());
            perror(error);
            exit(4);
        }
        numero = NULL;
    }
}

int main(void) {
    if (creaComp() == 0) {
        printf("Memoria compartida creada con éxito: %d\n", *numero);
        borraComp();
    }
    return 0;
}
