// sim_pos: genera una secuencia aleatoria de valores de posicionamiento
// para el robot explorador en el rango 'A'..'Z'
///////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

#define N_DATOS 10  // Longitud de la secuencia generada

main (int argc, char* argv[])
{
    char p;
    int i;

    if (argc > 2)
    {
        fprintf(stderr, "Uso: %s posicion_inicial > fichero_salida\n", argv[0]);
        exit(1);
    }

    if (argc == 1) p= 'N';
    else p= argv[1][0];

    srandom(time(NULL));

    for (i=0; i<N_DATOS; i++) {
        write (1, &p, 1);
        sleep(random()%5+1);
        p= p+random()%7-3;
        if (p<'A') p= 'A';
        if (p>'Z') p= 'Z';
     }
}
