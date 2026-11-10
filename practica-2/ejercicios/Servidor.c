#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/socket.h> // struct sockaddr -- formato genérico
#include <netinet/in.h> // struct sockaddr_in -- formato cómodo

#define PUERTO 9999

void manejo_errores (int variable, const char *mensaje) {
    if (variable < 0) {
        perror(mensaje);
        exit(1);
    }
}

int conexion_socket() {
    int conector = socket(AF_INET, SOCK_STREAM, 0);
    manejo_errores(conector, "Error en socket");

    struct sockaddr_in ipRedPuerto = {0};

    ipRedPuerto.sin_family = AF_INET; // tipo de red
    ipRedPuerto.sin_port = htons(PUERTO); // para puertos de red
    ipRedPuerto.sin_addr.s_addr = htonl(INADDR_ANY); // para direcciones IP

    int auxBind = bind(conector, (struct sockaddr *) &ipRedPuerto, sizeof(ipRedPuerto));
    manejo_errores(auxBind, "Error al conectar el socket al puerto");

    int auxListen = listen(conector, 10);
    manejo_errores(auxListen, "Error al poner el servidor a escuchar");

    return conector;
}

int abrir_archivo (const char *archivo) {
    int desc_archivo = open(archivo, O_RDONLY);
    manejo_errores(desc_archivo, "Error al abrir el archivo");
    return desc_archivo;
}

void lectura_archivo (int origen, int destino) {
    char buffer[4096]; // 4k
    ssize_t total_leidos;

    while ((total_leidos = read(origen,buffer,sizeof(buffer))) > 0) {
        write(destino,buffer,total_leidos);
    }

    close(origen);
    close(destino);
}

void llegada_cliente (int conector_servidor, int conector_cliente, const char *archivo) {
    pid_t pid = fork();
    manejo_errores(pid, "Error al crear hijo");

    if (pid == 0) {
        close(conector_servidor);
        int origen = abrir_archivo(archivo);
        lectura_archivo(origen,conector_cliente);
        exit(0);
    } else {
        close(conector_cliente);
    }
}

void manejador(int senial) {
    wait(NULL);
    signal(SIGCHLD, manejador);
}

int main() {
    const char *archivo = "Google.html";
    int conector_servidor = conexion_socket();

    signal(SIGCHLD, manejador);
    int conector_cliente;
    while(1) {
        conector_cliente = accept(conector_servidor,NULL,NULL); // no necesito consultar datos de quién se conectó
        manejo_errores(conector_cliente, "Error al conectar con el cliente");
        llegada_cliente(conector_servidor,conector_cliente,archivo);
    }
}