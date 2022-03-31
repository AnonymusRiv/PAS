#!/bin/bash
carpeta="$1"
horas="$2"

if [ $# -ne 2 ] || [ ! -d $1 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio5.sh <ruta_directorio> <num_horas>"
    exit

else
    let horas=(horas * 60)                              #lo recibiremos en minutos, pero nosotros queremos ponerlo en horas
    for x in $(find $carpeta -mmin -$horas -type f)     #busca en la carpeta todos los archivos que tengan un mínimo de $horas modificado
    do
        echo "$x"
    done
fi