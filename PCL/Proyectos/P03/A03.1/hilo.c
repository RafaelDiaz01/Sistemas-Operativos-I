#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/time.h>
#include <time.h>

#define N_DATOS_H2O 20
#define N_DATOS_CO2 20
#define N_DATOS_POS 10

// Estructura para pasar parámetros a los hilos
typedef struct {
    char initial_pos;
} thread_args;

// Variable global para el mutex (evitar mezcla de salidas)
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

// Función para el simulador de humedad (H2O)
void* sim_H2O(void* arg) {
    char s[2];
    srand(time(NULL) ^ pthread_self());

    for (int i = 0; i < N_DATOS_H2O; i++) {
        sleep(1);
        sprintf(s, "%1c", (int)rand() % 6 + 'a');
        
        pthread_mutex_lock(&mutex);
        write(1, s, 1);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_mutex_lock(&mutex);
    printf("\nHilo H2O terminado\n");
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

// Función para el simulador de CO2
void* sim_CO2(void* arg) {
    char s[2];
    srand(time(NULL) ^ pthread_self());

    for (int i = 0; i < N_DATOS_CO2; i++) {
        sleep(1);
        sprintf(s, "%1d", (int)rand() % 6);
        
        pthread_mutex_lock(&mutex);
        write(1, s, 1);
        pthread_mutex_unlock(&mutex);
    }
    
    pthread_mutex_lock(&mutex);
    printf("\nHilo CO2 terminado\n");
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

// Función para el simulador de posición
void* sim_pos(void* arg) {
    thread_args* args = (thread_args*)arg;
    char p = args->initial_pos;
    srand(time(NULL) ^ pthread_self());

    for (int i = 0; i < N_DATOS_POS; i++) {
        pthread_mutex_lock(&mutex);
        write(1, &p, 1);
        pthread_mutex_unlock(&mutex);
        
        sleep(rand() % 5 + 1);
        p = p + rand() % 7 - 3;
        if (p < 'A') p = 'A';
        if (p > 'Z') p = 'Z';
    }
    
    pthread_mutex_lock(&mutex);
    printf("\nHilo POS terminado\n");
    pthread_mutex_unlock(&mutex);
    
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    struct timeval inicio, fin;
    double tiempo_total;
    pthread_t hilo_H2O, hilo_CO2, hilo_pos;
    int rc;
    thread_args args;
    
    // Iniciar medición de tiempo
    gettimeofday(&inicio, NULL);
    
    // Establecer posición inicial (por defecto 'N')
    args.initial_pos = (argc > 1) ? argv[1][0] : 'N';
    
    // Crear hilo para sim_H2O
    rc = pthread_create(&hilo_H2O, NULL, sim_H2O, NULL);
    if (rc) {
        fprintf(stderr, "Error al crear hilo H2O: %d\n", rc);
        exit(EXIT_FAILURE);
    }
    
    // Crear hilo para sim_CO2
    rc = pthread_create(&hilo_CO2, NULL, sim_CO2, NULL);
    if (rc) {
        fprintf(stderr, "Error al crear hilo CO2: %d\n", rc);
        exit(EXIT_FAILURE);
    }
    
    // Crear hilo para sim_pos
    rc = pthread_create(&hilo_pos, NULL, sim_pos, (void*)&args);
    if (rc) {
        fprintf(stderr, "Error al crear hilo POS: %d\n", rc);
        exit(EXIT_FAILURE);
    }
    
    // Esperar a que todos los hilos terminen
    pthread_join(hilo_H2O, NULL);
    pthread_join(hilo_CO2, NULL);
    pthread_join(hilo_pos, NULL);
    
    // Finalizar medición de tiempo
    gettimeofday(&fin, NULL);
    
    // Calcular tiempo total en segundos
    tiempo_total = (fin.tv_sec - inicio.tv_sec) + 
                 (fin.tv_usec - inicio.tv_usec) / 1000000.0;
    
    printf("\nTodos los hilos han terminado.\n");
    printf("Tiempo total de ejecución: %.6f segundos\n", tiempo_total);
    
    // Destruir el mutex
    pthread_mutex_destroy(&mutex);
    
    pthread_exit(NULL);
}
