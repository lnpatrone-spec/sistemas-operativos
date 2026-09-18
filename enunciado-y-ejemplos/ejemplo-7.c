#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main() {
 printf("Voy a suicidarme\n");
 kill(getpid(), SIGKILL);
 perror("No he muerto???");
} 