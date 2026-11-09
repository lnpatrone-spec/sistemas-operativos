/* Este programa actúa como el ejecutable de destino. Entra en funcionamiento asumiendo el control
directo de un proceso preexistente que acaba de sustituir su contenido original. Su función consiste en
recibir los parámetros que le fueron transferidos desde el programa invocador, imprimirlos por pantalla
para validar la persistencia de los datos entre ambas etapas, sostener una breve espera y culminar
formalmente la ejecución del proceso en el sistema operativo. */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
    
int main (int argc, char *argv[]) {
    int i;
    printf ("Ejecutando el programa invocado (prog2). Sus argumentos son: \n");
 
    for ( i = 0; i < argc; i ++ ) {
        printf (" argv[%d] : %s \n", i, argv[i]);
    }
        sleep(10);
        exit (0);
} 
