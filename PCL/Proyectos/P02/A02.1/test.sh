#!/bin/bash
./stee < ~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/dev/CO2 | ~/Documentos/SextoSemestre/Sistemas-Operativos-I/PCL/Proyectos/P02/./MCPV > para_cifrar
./cencriptador < para_cifrar salida_cifrada
rm para_cifrar
echo "Resultado exitoso"
