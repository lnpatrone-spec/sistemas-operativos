/* El programa demuestra cómo un proceso puede provocar su propia finalización inmediata enviándose
una orden de detención del sistema. Tras mostrar un aviso previo, el proceso consulta su propia identidad
y se dirige a sí mismo una instrucción no interceptable ni cancelable, lo que ocasiona su cierre en ese
preciso instante e impide por completo alcanzar las líneas posteriores. */

#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
 printf("Voy a suicidarme\n");
 kill(getpid(), SIGKILL);
 perror("No he muerto???");
} 
