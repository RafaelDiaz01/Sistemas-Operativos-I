#!/bin/bash

# Guardamos el tiempo de inicio
start_time=$(date +%s.%N)

# Ejecutamos programas en paralelo
~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/Proyectos/P03/A03.1/sim_CO2 &
~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/Proyectos/P03/A03.1/sim_H2O &
~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/Proyectos/P03/A03.1/sim_pos &

wait

# Se calcula el tiempo transcurrido
end_time=$(date +%s.%N)
elapsed_time=$(echo "$end_time - $start_time" | bc)

# Mostrar el tiempo de ejecución
echo
echo "---------------------------------"
echo "Tiempo de ejecución paralela: $elapsed_time segundos"
echo "---------------------------------"

