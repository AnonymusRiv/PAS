#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio6.sh <usuario>"
    exit
fi

usuario="$1" #variable global

crear_usuario(){
    contador=0
    for user in $(cat users.txt)
    do
        if [[ $user == $usuario ]] #si se encuentra el nombre $user en el fichero
        then
            echo "Ya se encuentra el usuario $usuario"
            let "contador = contador + 1"
            exit
        fi
    done
    if [[ $contador == 0 ]]
    then
        echo -e $usuario >> users.txt #-e es para que coja el salto de linea  ("\n")-n es para que no meta otro salto de linea al final del fichero
        mkdir homes/$usuario
        cp skel/* homes/$usuario
        echo "Se ha creado el usuario $usuario"
    fi
}

crear_usuario