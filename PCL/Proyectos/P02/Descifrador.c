#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

#define MAX_KEY_LENGTH 256

int get_password(char *password, size_t max_length) {
	struct termios old_term, new_term;
    
	// Deshabilitar eco en la terminal
	if (tcgetattr(STDIN_FILENO, &old_term) != 0) {
    	perror("tcgetattr");
    	return -1;
	}
    
	new_term = old_term;
	new_term.c_lflag &= ~ECHO;
    
	if (tcsetattr(STDIN_FILENO, TCSANOW, &new_term) != 0) {
    	perror("tcsetattr");
    	return -1;
	}
    
	// Leer la clave
	printf("Introduzca la clave de descifrado: ");
	if (fgets(password, max_length, stdin) == NULL) {
    	password[0] = '\0';
    	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
    	return -1;
	}
    
	// Eliminar el salto de línea final
	password[strcspn(password, "\n")] = '\0';
    
	// Restaurar configuración de terminal
	tcsetattr(STDIN_FILENO, TCSANOW, &old_term);
	printf("\n");
	return 0;
}


void descifrar(FILE *entrada, FILE *salida, const char *clave) {
	int c;
	size_t clave_len = strlen(clave);
	size_t clave_pos = 0;
    
	while ((c = fgetc(entrada)) != EOF) {
    	// Mostrar en salida estándar
    	putchar(c);
   	 
    	// Descifrar carácter
    	if (clave_len > 0) {
        	c ^= clave[clave_pos];
        	clave_pos = (clave_pos + 1) % clave_len;
    	}
   	 
    	// Escribir descifrado en archivo de salida
    	if (salida != NULL) {
        	fputc(c, salida);
    	}
	}
}

int main(int argc, char *argv[]) {
	if (argc != 3) {
    	fprintf(stderr, "Uso: %s entrada-cifrada salida-descifrada\n", argv[0]);
    	return 1;
	}
    
	char clave[MAX_KEY_LENGTH];
	if (get_password(clave, MAX_KEY_LENGTH) != 0) {
    	fprintf(stderr, "Error al leer la clave\n");
    	return 2;
	}
    
	FILE *entrada = fopen(argv[1], "rb");
	if (entrada == NULL) {
    	perror("Error al abrir archivo de entrada");
    	return 3;
	}
    
	FILE *salida = fopen(argv[2], "wb");
	if (salida == NULL) {
    	perror("Error al abrir archivo de salida");
    	fclose(entrada);
    	return 4;
	}
    
	// Procesar archivos
	descifrar(entrada, salida, clave);
    
	// Cerrar archivos
	fclose(entrada);
	fclose(salida);
    
	return 0;
}
