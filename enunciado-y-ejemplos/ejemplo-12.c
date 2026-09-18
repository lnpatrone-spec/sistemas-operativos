#include <string.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *env[]) {
    int df, cont=0;
    char buffer[4096];
    df=creat("variables.txt", 0755);
    
    if (df<0) {
        perror("Error al crear archivo");
        exit(-1);
    }
 
    while (env[cont] != NULL) {
        snprintf(buffer, sizeof(buffer), "%s\n", env[cont]);
 
        if (write(df, buffer, strlen(buffer)) != strlen(buffer)) {
            perror("Error al escribir");
            break; /* NO SIGUE */
        }
        cont++;
    }
    close(df);
}