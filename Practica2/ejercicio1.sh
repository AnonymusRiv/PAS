#!/bin/bash

# la salida de ps se pasa a sed
# necesitamos las flags -rne: -r: utiliza ERE, -n: silencioso, -e: ejecutar comando
# 1! hace que ignore la primera linea (que es el titulo de tabla)
# los parentesis guardan la informacion
# el . selecciona un caracter cualquiera
# el * Selecciona ninguna, una o varias veces lo anterior
# el $ nos lleva hasta el final de la linea
# \1/ devuelve lo primero que guardes que los parentesis si pones 2 lo 2do...
# el sort los ordena alfabeticamente
# el uniq hace que no se repitan
for user in $(ps aux | sed -rne '1!s/^([^ ]+).*$/\1/p' | sort | uniq);
do
    suma=0                                                      #Se crea una variable para ir almacenando la suma de los cpu
    #este es igual pero para cada usuario guarda entre parentesis la 3ra columna y la vuelve a agrupar
    for cpu in $(ps aux | sed -rne '1!s/^'$user'[ ]+[^ ]+[ ]+([^ ]+).*/\1/p' | sort | uniq);
    do
        suma=$(echo "$suma + $cpu" | bc)                        #se le pasa a bc (calculadora en linea de comandos la expresion a calcular) y se guarda en la variable suma
    done
    echo "$user esta haciendo un uso de cpu del $suma%"         #Se muestra por pantalla el usuario y la cantidad en % que usa dicho usuario
done