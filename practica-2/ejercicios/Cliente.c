#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PUERTO 9999

void manejo_errores (int variable, const char *mensaje) {
    if (variable < 0) {
        perror(mensaje);
        exit(1);
    }
}

void manejo_argumentos (int variable) {
    if (variable != 2) {
        printf("Uso correcto: Cliente IP_Servidor\n");
        exit(1);
    }
}

int conexion_socket(char *ip) {
    int conector_cliente = socket(AF_INET, SOCK_STREAM, 0);
    manejo_errores(conector_cliente, "Error en socket");

    struct sockaddr_in ipRedPuerto = {0};

    ipRedPuerto.sin_family = AF_INET;
    ipRedPuerto.sin_port = htons(PUERTO);
    ipRedPuerto.sin_addr.s_addr = inet_addr(ip); // dirección IP pasada por el usuario traducida

    int auxCon = connect(conector_cliente, (struct sockaddr *) &ipRedPuerto, sizeof(ipRedPuerto));
    manejo_errores(auxCon, "Error al conectar el cliente");

    return conector_cliente;
}

void lectura_socket (int conector_cliente) {
    char buffer[4096]; // 4k
    ssize_t total_leidos;

    while ((total_leidos = read(conector_cliente, buffer, sizeof(buffer))) > 0) {
        write(1,buffer,total_leidos);
    }
    
    close(conector_cliente);
}

int main(int argc, char *argv[]) {
    manejo_argumentos(argc);
    int conector_cliente = conexion_socket(argv[1]);
    lectura_socket(conector_cliente);
    exit(0);
}