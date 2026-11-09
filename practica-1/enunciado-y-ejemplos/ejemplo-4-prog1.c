/* Este programa actúa como invocador inicial. Al arrancar, recibe un conjunto de parámetros desde la
línea de comandos, los muestra por pantalla y, tras una breve pausa temporal, sustituye de forma
completa su propia lógica de ejecución por la de un segundo programa ejecutable, transfiriéndole los
argumentos recibidos. Mediante esto, el programa original delega el control al nuevo programa sin
necesidad de crear un proceso adicional, conservando la misma entidad operativa ante el sistema. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main (int argc, char *argv[]) {
    int i;
    printf ("\nEjecutando el programa invocador (prog1). Sus argumentos son: \n");
    
        for ( i = 0; i < argc; i ++ ) {
        printf (" argv[%d] : %s \n", i, argv[i]);
        }
        sleep( 10 );
        strcpy (argv[0],"prog2");
        

        if (execvp ("./prog2", argv) < 0) {
        printf ("Error en la invocacion a prog2 \n");
        exit (1);
        };

    exit (0);
} 
