/* El programa programa un temporizador y define una respuesta personalizada para reaccionar a una
interrupción generada por el sistema. Tras configurar la rutina y fijar una cuenta regresiva de unos
segundos, el proceso detiene su actividad y entra en espera pasiva. Al cumplirse el tiempo, el
sistema despierta al proceso y ejecuta de inmedato la rutina asignada para notificar el evento 
temporal. Una vez atendida la interrupción, el programa retoma su flujo de ejecución ordinario
en el punto exacto donde quedó detenido y finaliza su marcha. */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void alarma() {
    printf("acabo de recibir un SIGALRM\n");
}

int main() {
    signal(SIGALRM,alarma);
    printf("Acabo de programar la captura de un SIGALRM\n");
    alarm(3);
    printf("Ahora he programado la alarma en 3 seg.\n");
    pause();
    printf("Ahora continúo con la ejecución normal\n");
} 
