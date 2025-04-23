#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define CLAVE 0x08
#define TAM_BUFFER 1

int main(int argc, char* argv[]) {
    int fd_salida;
    char buffer[TAM_BUFFER];
    ssize_t bytes_leidos;
    
    if (argc != 2) {
        write(STDERR_FILENO, "Uso: ./programa archivo_salida\n", 30);
        exit(1);
    }

    if ((fd_salida = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0) {
        write(STDERR_FILENO, "Error al abrir archivo\n", 22);
        exit(2);
    }

    while ((bytes_leidos = read(STDIN_FILENO, buffer, TAM_BUFFER)) > 0) {
        write(STDOUT_FILENO, buffer, bytes_leidos);  // Mostrar original
        
        if (buffer[0] != '\n') {
            buffer[0] ^= CLAVE;  // Cifrado XOR
            write(fd_salida, buffer, bytes_leidos);
        } else {
            write(fd_salida, "\n", 1);
        }
    }

    close(fd_salida);
    return 0;
}