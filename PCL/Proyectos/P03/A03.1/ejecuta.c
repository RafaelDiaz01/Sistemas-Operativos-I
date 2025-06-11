#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) 
{
    if (argc < 2) {
        fprintf(stderr, "Estas usando mal %s programa1\n", argv[0]);
        exit(1);
    }

    for (int i = 1; i < argc; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            perror("Error al crear proceso hijo");
            continue;
        }
        
        if (pid == 0) { // Proceso hijo
            printf("Ejecutando: %s\n", argv[i]);
            if (execlp(argv[i], argv[i], NULL) == -1) {
                fprintf(stderr, "Error: no se pudo ejecutar %s\n", argv[i]);
                exit(EXIT_FAILURE);
            }
        }
    }
    
    // Esperar a que todos los procesos hijos terminen
    int status;
    while (wait(&status) > 0);
    
    printf("Todos los programas han sido ejecutados\n");
    return 0;
}
