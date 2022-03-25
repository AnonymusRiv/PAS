#!/bin/bash
carpeta="$1"
horas="$2"

if [ $# -ne 2 ] || [ ! -d $1 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio5.sh <ruta_directorio> <num_horas>"
    exit

else
    let horas=(horas * 60)
    for x in $(find $carpeta -mmin -$horas -type f)
    do
        echo "$x"
    done
fi