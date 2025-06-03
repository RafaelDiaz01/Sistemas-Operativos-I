#!/bin/bash

# Con esta instrucción guardamos el tiempo de inicio, asi como dice el documento.
start_time=$(date +%s.%N)

# Se ejecutam los programas de manera secuencial.
~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/Proyectos/P03/A03.1/sim_CO2
~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/Proyectos/P03/A03.1/sim_H2O
~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/Proyectos/P03/A03.1/sim_pos

# Se calcula el tiempo transcurrido
end_time=$(date +%s.%N)
elapsed_time=$(echo "$end_time - $start_time" | bc)

# Mostramos el tiempo de ejecución
echo
echo "------------------------------------------------------"
echo "Tiempo de ejecución secuencial: $elapsed_time segundos"
echo "------------------------------------------------------"
