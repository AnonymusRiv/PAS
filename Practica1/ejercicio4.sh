#!/bin/bash

carpeta="$1"
n=0

if [ $# -ne 1 ] || [ ! -d $1 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio4.sh <directorio>"
    exit
fi

for x in $(find $carpeta)
do
    if [ ! -d $x ]
    then
        let n=n+1
        nombre=$(basename $x)
        caracteres=$(echo -n $nombre | wc -m)
        echo -e "$n \t $nombre \t $caracteres"
    fi
done
