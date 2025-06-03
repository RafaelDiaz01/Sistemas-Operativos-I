//cencriptador.c con funciones de bibliotecca

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>   

//clave de 4 bits hexadecimal
#define CLAVE 0x08

int main(int argc, char* argv[])
{
    struct timeval start, end;	//Declaración de estructura para cronometrar
 
    gettimeofday(&start, NULL);	//Obtener tiempo de inicio
    FILE* fd;
    int c;

    if ((argc != 2)) {
        fprintf(stderr, "Uso: %s Fichero_salida\n", argv[0]);
        exit(1);
    }

    if ((fd= fopen(argv[1], "w")) == NULL) {
        fprintf(stderr, "No se puede abrir para escritura en %s\n", argv[1]);
        exit(2);
    }

    while ((c=getc(stdin)) != EOF) {
        putc(c, stdout); //Imprimir por la salida estandar
	if(c !='\n'){
	   char cifrado = c^CLAVE;	//cifrar
	   putc(cifrado, fd);	//Escribir en fichero
	}
	else{
	   putc('\n', fd);	//escribir en fichero
	}
    }
    fclose(fd);

    //gettimeofday(&end, NULL);	//Obtener tiempo de finalizacion
 
    //long seconds = (end.tv_sec - start.tv_sec);		//Obtener segundos
    //long micros = ((seconds * 1000000) + end.tv_usec - start.tv_usec);
 
    //printf("Ejecucion finalizada en %li segundos o %li  microsegundos\n", seconds, micros);
}


