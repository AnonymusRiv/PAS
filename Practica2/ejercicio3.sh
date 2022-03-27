#!/bin/bash

fichero="$1"

if [ $# -ne 1 ] || [ ! -e $fichero ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio3.sh <archivo_de_texto>"
    exit
fi


for palabra in $(cat texto.txt) #guarda en $palabra cada linea del fichero $fichero
do
    #TODO Quitar puntos y comas
    caracteres=$(echo -n $palabra | wc -m)
    echo $palabra $'\t' $caracteres
done | sort | uniq | nl