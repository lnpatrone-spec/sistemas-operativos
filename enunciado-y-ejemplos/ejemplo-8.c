/* El programa imprime líneas numeradas sin parar mientras cuenta cuántas lleva mostradas. Al mismo
tiempo, programa un temporizador de 5 segundos. Cuando se cumple ese tiempo, una alarma detiene el
bucle y el programa muestra el total de líneas impresas antes de terminar. */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int seguir = 1; /* Variable global */

void fin(int n) {
    seguir = 0;
}

int main() {
 int contador = 0;
 signal(SIGALRM, fin);
 alarm(5);
 do {
 printf("Esta es la línea %d\n", contador++);
 } while (seguir);
 printf("TOTAL: %d líneas\n", contador);
}
