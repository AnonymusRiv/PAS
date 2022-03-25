#!/bin/bash

suma() {
    let "$1 + $2" | bc
}

ps aux | sed -r -n -e ''

echo "$user está haciendo un uso de cpu del $porcentaje"


<< 'Comment'
df | sed -r -n -e '2,$s/^[^ ]+[ ]+[^ ]+/Hola/p'


df | sed -r -n -e '2,$s/^([a-Z0-9/:\\]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9]+)[ ]+([0-9]+%)[ ]+([a-Z0-9/]+)/El sistema de ficheros \1, esta montado en \6, tiene un tamaño de \2 de los cuales se estan usando \3 que representan un porcentaje de \5 del total. Quedan libres \4./p'
Comment

echo
