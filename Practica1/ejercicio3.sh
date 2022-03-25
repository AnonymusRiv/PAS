#!/bin/bash

nombre=$1-/

if [ $# -ne 3 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio3.sh <directorio_origen> <directorio_destino>"
    exit

elif [ $nombre -mtime 1-type f ] #se ha hecho la copia el mismo dia
then
    echo "Ya se ha realizado esta copia hoy ($nombre)"
    exit

elif [ ! -e $1  ] #no existe el nombre de la carpeta
then
    echo "$1 no existe"
    exit

else
    #crea la copia
    if [ ! -e $2 ]#mira su existe $2. Si no existe lo crea
    then
        mkdir $1$2
    fi
    tar -cvzf $nombre.tar.gz $1$2

fi

# tar -cvzf nombre.tar.gz ruta