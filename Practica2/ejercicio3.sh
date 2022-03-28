#!/bin/bash

fichero="$1"

if [ $# -ne 1 ] || [ ! -e $fichero ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio3.sh <archivo_de_texto>"
    exit
fi

for palabra in $(cat texto.txt) #guarda en $palabra cada linea del fichero $fichero
do
    echo $palabra | tr -d ",|." >> texto2.txt  #TODO poner bonito
done

for palabra in $(cat texto2.txt) #guarda en $palabra cada linea del fichero $fichero
do
    caracteres=$(echo -n $palabra | wc -m)
    echo $palabra $'\t' $caracteres
done | sort | uniq | nl

rm texto2.txt




if [ $# != 1 ]
then
    echo "Número de parámetros incorrecto"
else
    for word in $(cat $1 | tr '.' ',' | sed 's/,//g' | sed 's/[A-Z]/\L&/g')
    do
        echo -e "$word  ${#word}"
    done | sort | uniq | nl
fi