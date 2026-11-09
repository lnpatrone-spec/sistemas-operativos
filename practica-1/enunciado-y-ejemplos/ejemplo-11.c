/* El programa abre el canal del terminal para solicitar datos al usuario de manera directa. Una
vez abierto, lee un número introducido por teclado, calcula su doble y muestra el resultado final
por pantalla antes de cerrar el acceso al terminal. */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int df,tam;
    long numero;
    char buffer[10];
    df=open("/dev/tty", O_RDONLY);
    
    if (df<0) {
        perror("Error al abrir tty");
        exit(-1);
    }
 
    tam=read(df, buffer, 9); /* COMO MUCHO DE HASTA 9 DIGITOS */
    
    if (tam == -1) {
        perror("Error de lectura");
    } else {
        buffer[tam]=0; /* PONE EL FINAL DE CADENA */
        numero=atoi(buffer);
        printf("Resultado: %ld\n",numero*2);
    }
 close(df);
} 
