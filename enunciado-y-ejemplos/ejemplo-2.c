/* El programa crea un proceso hijo para demostrar que los procesos no comparten sus variables en memoria,
sino que cada uno trabaja con una copia privada e independiente. Tras dividirse, el proceso hijo
inicializa una variable en cero y la incrementa en varias iteraciones para generar y mostrar
números pares, mientras que el proceso padre inicializa la misma variable en uno y realiza los mismos
incrementos para mostrar números impares. Las modificaciones hechas por un proceso no afectan al otro,
demuestra el aislamiento de memoria entre ambos antes de finalizar. */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main ( ) {
    int i;
    int j;
    pid_t pid;
    pid = fork( );
 
    switch (pid) {
    case -1:
        printf ("\nNo he podido crear el proceso hijo");
        break;
    case 0:
        i = 0;
        printf ("\nSoy el hijo, mi PID es %d y mi variable i (inicialmente a %d) es par", getpid(), i);
        
        for ( j = 0; j < 5; j ++ ) {
            i ++;
            i ++;
            printf ("\nSoy el hijo, mi variable i es %d", i); 
        };
        break;
    default:
        i = 1;
        printf ("\nSoy el padre, mi PID es %d y mi variable i (inicialmente a %d) es impar", getpid(), i);
        
        for ( j = 0; j < 5; j ++ ) {
            i ++;
            i ++;
        printf ("\nSoy el padre, mi variable i es %d", i);
        };
    };
    printf ("\nFinal de ejecucion de %d \n", getpid());
    exit (0);
}
