/* El programa muestra el ciclo de vida de una rutina de atención a interrupciones y su reestablecimiento
automático al comportamiento por defecto. En un primer momento, programa un temporizador y captura con éxito
la señal resultante mediante una función propia. Sin embargo, al configurar un segundo temporizador sin
volver a registrar dicha función, el sistema recurre a su acción predeterminada al cumplirse el tiempo,
lo que provoca la terminación forzosa del proceso e impide que se alcance la última línea del flujo. */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarma() {
 printf("acabo de recibir un SIGALRM\n");
}
int main(){
    signal(SIGALRM,alarma);
    printf("acabo de programar la captura de un SIGALRM\n");
    alarm(3);
    printf("Ahora he programado la alarma en 3 seg.\n");
    pause();
    printf("vuelvo a programar la alarma\n");
    alarm(3);
    pause();
    printf("En POSIX esta línea nunca se ejecutaría porque me ha matado el SIGALRM\n");
} 
