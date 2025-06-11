//Descifrador.c

#include <unistd.h>
#include <termios.h>
#include <stdio.h>
#include <stdlib.h>
#define CLAVE 0x08

//Funcion de desactivar echo
int cambia_eco ()
{
    int r;
    struct termios tm;

    tcgetattr(0, &tm);
    if (tm.c_lflag & ECHO) {
            r= 1;
            tm.c_lflag &= ~ECHO;
    }
    else {
            r= 0;
            tm.c_lflag |= ECHO;
    }
    tcsetattr(0, TCSANOW, &tm);
    return (r);
}



void main (int argc, char* argv[])
{

    int c, i, est;
    FILE *fichero1, *fichero2;

    printf("ingrese clave hexadecimal: ");

	//Desactiva eco
    est = cambia_eco();
	//Leer clave
    scanf("%d", &i);
    est = cambia_eco();

	if (i != CLAVE) {
		fprintf(stderr, "Clave incorrecta\n");
		exit(1);
	}

    if ((fichero1= fopen(argv[1], "r")) == NULL) {
       fprintf(stderr, "No se puede leer de %s\n", argv[1]);
       exit(1);
    }
    if ((fichero2= fopen(argv[2], "w")) == NULL) {
       fprintf(stderr, "No se puede escribir en %s\n", argv[2]);
       exit(1);
    }

    while ((c=getc(fichero1)) != EOF) {
        if (c !='\n') 
        	putc(c^i, fichero2);
        else 
        	putc(c, fichero2);
    }
    fclose(fichero2);
}



