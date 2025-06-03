// sim_H2O: genera una secuencia aleatoria de valores del sensor de humedad
// para el robot explorador en el rango 'a'..'f'
///////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define N_DATOS 20  // Longitud de la secuencia generada

main (int argc, char* argv[])
{
    char s[2];
    int i;

    if (argc != 1)
    {
        fprintf(stderr, "Uso: %s > fichero_salida\n", argv[0]);
        exit(1);
    }

    srandom(getpid());

    for (i=0; i<N_DATOS; i++) {
        sleep(1);
        sprintf(s, "%1c", (int)random()%6+'a');
        write (1, &s, 1);
    }
}
