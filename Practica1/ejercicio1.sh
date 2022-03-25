#!/bin/bash

ruta="$1/"
subdirectorios="$2"
longitud="$3"

extensiones=( ".sh" ".html" ".key" ".txt" )

random () {
    tr -dc A-Za-z0-9 < /dev/urandom | head -c $longitud
}


if [ $# -ne 3 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio1.sh <ruta_directorio> <num_subdirectorios> <longitud>"
    exit
fi

if [ -d $ruta ]
then
    echo "¿Quiere eliminar la carpeta:? s/n"
    read  -s -n1 confirmacion
    if [ $confirmacion == "s" ]
    then
        rm -r $ruta
    else
        echo "Carpeta no eliminada"
        exit
    fi
fi

mkdir $ruta
for ((i=0; $i<$subdirectorios; i=$i+1))
do
    nombre="$(random)"
    mkdir $ruta$nombre
    for ext in ${extensiones[*]}
    do
        touch $ruta$nombre/$(random)$ext
    done
done