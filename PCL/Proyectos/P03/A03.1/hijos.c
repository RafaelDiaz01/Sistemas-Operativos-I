#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <time.h>

#define N_DATOS 20  // Para H2O y CO2
#define N_DATOS_POS 10  // Para posición

void sim_H2O() {
    char s[2];
    srand(getpid());

    for (int i = 0; i < N_DATOS; i++) {
        sleep(1);
        sprintf(s, "%1c", (int)rand() % 6 + 'a');
        write(1, s, 1);
    }
    printf("\nProceso H2O terminado\n");
}

void sim_CO2() {
    char s[2];
    srand(getpid());

    for (int i = 0; i < N_DATOS; i++) {
        sleep(1);
        sprintf(s, "%1d", (int)rand() % 6);
        write(1, s, 1);
    }
    printf("\nProceso CO2 terminado\n");
}

void sim_pos(char initial_pos) {
    char p = initial_pos;
    srand(time(NULL));

    for (int i = 0; i < N_DATOS_POS; i++) {
        write(1, &p, 1);
        sleep(rand() % 5 + 1);
        p = p + rand() % 7 - 3;
        if (p < 'A') p = 'A';
        if (p > 'Z') p = 'Z';
    }
    printf("\nProceso POS terminado\n");
}

int main(int argc, char *argv[]) {
    struct timeval inicio, fin;
    double tiempo_total;
    
    // Iniciar medición de tiempo
    gettimeofday(&inicio, NULL);
    
    pid_t pid1, pid2, pid3;
    int status;
    
    // Crear primer proceso (sim_H2O)
    pid1 = fork();
    if (pid1 == 0) {
        sim_H2O();
        exit(0);
    } else if (pid1 < 0) {
        perror("Error al crear el primer proceso");
        exit(1);
    }
    
    // Crear segundo proceso (sim_CO2)
    pid2 = fork();
    if (pid2 == 0) {
        sim_CO2();
        exit(0);
    } else if (pid2 < 0) {
        perror("Error al crear el segundo proceso");
        exit(1);
    }
    
    // Crear tercer proceso (sim_pos)
    pid3 = fork();
    if (pid3 == 0) {
        char initial_pos = (argc > 1) ? argv[1][0] : 'N';
        sim_pos(initial_pos);
        exit(0);
    } else if (pid3 < 0) {
        perror("Error al crear el tercer proceso");
        exit(1);
    }
    
    // Esperar a que todos los procesos hijos terminen
    waitpid(pid1, &status, 0);
    waitpid(pid2, &status, 0);
    waitpid(pid3, &status, 0);
    
    // Finalizar medición de tiempo
    gettimeofday(&fin, NULL);
    
    // Calcular tiempo total en segundos
    tiempo_total = (fin.tv_sec - inicio.tv_sec) + 
                 (fin.tv_usec - inicio.tv_usec) / 1000000.0;
    
    printf("\nTodos los procesos han terminado.\n");
    printf("Tiempo total de ejecución: %.6f segundos\n", tiempo_total);
    
    return 0;
}
