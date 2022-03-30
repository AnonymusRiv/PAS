#!/bin/bash

#Realiza un script que reciba como argumento un fichero de texto que contendrá una serie de direcciones IP de servidores DNS y
#realizará un ping a cada uno de ellos para comprobar la latencia media de los mismos. Además, se pasarán otros dos argumentos 
#que indicarán el número de pings realizados a cada IP y el timeout.
#Al final, se deberá mostrar una lista de las direcciones y el tiempo medio de respuesta de cada uno ordenados de forma ascendente por el tiempo. 
#Si alguna dirección no ha respondido en el tiempo indicado, se deberá mostrar al final de la lista.

if [ $# != 3 ]
then
    echo "Número de parámetros incorrecto. Uso: ./ejercicio2.sh <archivo_de_texto> <pings> <timeout>"
else
    for ip in $(cat $1)
    do
        for avgLat in $(ping -c $2 -W $3 -q $ip | grep '^r' | awk -F/ '{print$5}')
        do
            echo "$ip tiene una latencia media de $avgLat ms"
        done
    done | sort -n -k 7
    for ip in $(cat $1)
    do
        for ping in $(ping -c $2 -W $3 $ip)
        do
            if [ $? != 0 ]
            then
                echo -e "\nLa IP $ip no respondió en $3 segundos"
            fi
        done
    done
    
fi