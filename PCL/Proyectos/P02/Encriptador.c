#include <stdio.h>
#include <stdlib.h>

#define CLAVE 0x08  // Clave de cifrado de 4 bits

int main(int argc, char* argv[]) {
    FILE *archivo_salida;
    int caracter;
    
    // Validación de argumentos
    if (argc != 2) {
        fprintf(stderr, "Uso: %s archivo_salida\n", argv[0]);
        return 1;
    }
    
    // Apertura del archivo de salida
    if ((archivo_salida = fopen(argv[1], "wb")) == NULL) {
        fprintf(stderr, "Error al abrir %s para escritura\n", argv[1]);
        return 2;
    }
    
    // Procesamiento de la entrada
    while ((caracter = getchar()) != EOF) {
        putchar(caracter);  // Mostrar original en salida estándar
        
        if (caracter != '\n') {
            char cifrado = caracter ^ CLAVE;  // Operación XOR para cifrar
            putc(cifrado, archivo_salida);   // Escribir cifrado en archivo
        } else {
            putc('\n', archivo_salida);      // Conservar saltos de línea
        }
    }
    
    fclose(archivo_salida);
    return 0;
}