#!/bin/bash

if [ $# -ne 1 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio6.sh <usuario>"
    exit
fi

usuario="$1" #variable global

crear_usuario(){                    #esto es una funcion
    for user in $(cat users.txt)
    do
        if [[ $user == $usuario ]] #si se encuentra el nombre $user en el fichero
        then
            echo "Ya se encuentra el usuario $usuario"
            exit
        fi
    done
    echo -e $usuario >> users.txt #-e es para que coja el salto de linea  ("\n")-n es para que no meta otro salto de linea al final del fichero escribe en el fichero users.txt el nombre del usuario
    mkdir homes/$usuario
    cp skel/* homes/$usuario
    echo "Se ha creado el usuario $usuario"
}

crear_usuario