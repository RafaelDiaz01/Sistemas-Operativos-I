
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char* argv[])

{
    char c; //int c;
    int i;
    float j;

    FILE *archivo;
    
   /* if (**argv[1] != "<")) {
        fprintf(stderr, "Uso: %s MCPV no acepta párametros\n", argv[1]);
        exit(1);
    }*/

    c = getchar();
    archivo = fopen ("errores", "w");

    while (c != EOF) {

        i =(int)(c-'0');

	    if(i>=0 & i<=5){
	    	j=(float)i/(float)5;//1
	    	fprintf(stdout, "%.1f\n",j);
	    }
	    else{
	    	fprintf(archivo,"Error con: %d\n", i);
	    }
	    	c=getchar();
	    }

    fclose(archivo);

}

// RECIBE PARÁMETROS POR TECLADO
// MUESTRA LOS ERRORES EN "errores"
// MUESTRA LAS PROBABILIDADES EN PANTALLA
//  gcc -o MCPV MCPV.c
// ./MCPV


// RECIBE LOS PARÁMETROS DEL ARCHIVO "CO2"
// MUESTRA LOS ERRORES EN "errores"
// MUESTRA LAS PROBABILIDADES EN "Probabilidades"
// gcc -o MCPV MCPV.c
// ./MCPV <./CO2> Probabilidades





