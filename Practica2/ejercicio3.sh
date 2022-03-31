#!/bin/bash

fichero="$1"

if [ $# -ne 1 ] || [ ! -e $fichero ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio3.sh <archivo_de_texto>"
    exit
else
    for word in $(cat $fichero | tr '.' ',' | sed 's/,//g' | sed 's/[A-Z]/\L&/g')   #tr elimina los . y las ,
    do
        echo -e "$word  ${#word}"
    done | sort | uniq | nl
fi