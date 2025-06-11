

#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define TAMANO_BUFFER 1

main(int argc, char* argv[])
{
    int n;
    char buf[TAMANO_BUFFER];
    int fd;
    /*
    if (argc != 2) {
        fprintf(stderr, "Uso: %s fichero_salida\n", argv[0]);
        exit(1);
    }

    if ((fd= open(argv[1], O_WRONLY|O_CREAT, 0660)) < 0) {
        fprintf(stderr, "No se puede abrir para escritura %s\n", argv[1]);
        exit(2);
    }
    */
    while ((n= read(0, buf, TAMANO_BUFFER)) > 0) {
       write(1, buf, 1);
       write(fd, buf, 1);
       usleep(10000);
    }
}
    
