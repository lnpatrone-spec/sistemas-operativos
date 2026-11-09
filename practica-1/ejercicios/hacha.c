#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        perror("Argumentos incorrectos");
        return 1;
    }

    pid_t pid = 1;
    const char *nombreArchivo = argv[1];
    int bytes = atoi(argv[2]);

    struct stat info_archivo; // toda la parte de sacar cantidad total de archivos a crear
    if(stat(nombreArchivo,&info_archivo) < 0) {
        perror("Error al consultar el archivo");
        return 1;
    }
    long tamaño = info_archivo.st_size;
    int cantidad = tamaño / bytes;
        if (tamaño%bytes > 0) cantidad++;

    int descriptores[2];

    int df_origen = open(nombreArchivo,O_RDONLY);
    if(df_origen < 0) {
        perror("Error al abrir archivo original");
        return 1;
    }

    for (int i = 0; i < cantidad; i++) {
        pipe(descriptores);
        pid = fork();

        if (pid > 0) {
            close(descriptores[0]);

            char informacion[bytes];
            int leidos = read(df_origen,informacion,bytes);

            if (write(descriptores[1],informacion,leidos) < 0) {
                perror("Error en padre");
            }

            close(descriptores[1]);
            wait(NULL);
        } else {
            close(descriptores[1]);
            char buffer_hijo[bytes];
            char nombre_trozo[256];
            char extension[3];
            
            strcpy(nombre_trozo,nombreArchivo);
            strcat(nombre_trozo,".h");

            extension[0] = '0' + (i/10); // decenas
            extension[1] = '0' + (i%10); // unidades
            extension[2] = '\0'; // terminador

            strcat(nombre_trozo,extension);

            int df_destino = open(nombre_trozo, O_WRONLY | O_CREAT | O_TRUNC, 0666);
            if (df_destino < 0) {
                perror("Error al crear el trozo hijo");
                exit(1);
            }

            int leidos_tubo = read(descriptores[0],buffer_hijo, bytes);
            write(df_destino, buffer_hijo,leidos_tubo);

            close(df_destino);
            close(descriptores[0]);
            close(df_origen);
            exit(0);
        }
    }
    close(df_origen);
    return 0;
}