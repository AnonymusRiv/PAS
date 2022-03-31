#Desarrollar un script que permita generar un directorio con ficheros y subdirectorios de ejemplo
#que podrás utilizar en futuros ejercicios de esta práctica. El script recibirá 3 argumentos:
#1. Ruta del nuevo directorio que se va a crear.
#2. Número de subdirectorios que se crearán dentro del directorio principal.
#3. Longitud de los nombres de los ficheros (sin extensión) y subdirectorios.
#Al ejecutarlo, deberá crear un directorio principal en la ruta que se haya especificado en el primer
#parámetro. Dentro de ese directorio, se deber ́an crear N subdirectorios (indicado por el segundo
#parámetro) con nombres aleatorios de la longitud especificada por el tercer parámetro. Por
#último, dentro de cada uno de estos subdirectorios, se crear ́an 4 ficheros (vacíos) con nombres
#aleatorios y las extensiones .sh, .html, .key y .txt. Por ejemplo, si el número de subdirectorios
#es 2 y la longitud del nombre es 5, se podrían generar de la siguiente forma: CarpetaEjemplo

#!/bin/bash

ruta="$1/"
subdirectorios="$2"
longitud="$3"

extensiones=( ".sh" ".html" ".key" ".txt" )         #array de elementos que serán las terminaciones de los archivos

random () {                                         #función que genera nombres aleatorios
    tr -dc A-Za-z0-9 < /dev/urandom | head -c $longitud
}


if [ $# -ne 3 ]                                     #comprueba si el número de argumentos pasados por línea de comandos es 3
then
    echo "Argumentos incorrecto. Uso: ./ejercicio1.sh <ruta_directorio> <num_subdirectorios> <longitud>"
    exit
fi

if [ -d $ruta ]
then
    echo "¿Quiere eliminar la carpeta:? s/n"
    read  -s -n1 confirmacion                       #-s no hace echo de la entrada y -n1 es porque espera 1 caracter
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
    for ext in ${extensiones[*]}                    #para que tengan todas las extensiones
    do
        touch $ruta$nombre/$(random)$ext
    done
done

#otra forma de crear funciones es:
#function random() {}