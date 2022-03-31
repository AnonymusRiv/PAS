#!/bin/bash

carpeta="$1"

if [ $# -ne 1 ] || [ ! -d $1 ]              #si el número de argumentos introducido es incorrecto y el primer argumento no es una carpeta
then
    echo "Argumentos incorrecto. Uso: ./ejercicio4.sh <directorio>"
    exit
fi

for x in $(find $carpeta)   #mirara todos los archivos dentro de la carpeta, así como lor archivos dentro de otras carpetas que estén en esta
do
    if [ ! -d $x ]          #si no es un directorio
    then
        nombre=$(basename $x)                   #nombre solo cogerá el valor del archivo sin mostrar la ruta, para que muestre la ruta basta con eliminar esto y donde ponga $nombre poner $x
        caracteres=$(echo -n $nombre | wc -m)   #para contar el número de caracteres que tiene la linea
        echo -e "\t $nombre \t $caracteres"     #-e para que haga las tabulaciones y no imprima por pantalla \t
    fi
done | nl               #nl es para enumerarlos automáticamente cuando haga echo, no hace falta inidcarlo en el eco
