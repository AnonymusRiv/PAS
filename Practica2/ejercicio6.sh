#!/bin/bash

cifra="$1"


if [ $# -ne 1 ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio7.sh <cifra>"
    exit
fi

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

echo "1) Sistemas de ficheros cuyo número de bloques tenga al menos $cifra cifras"

for bloques in $(df | sed -rne '1!s/^[^ ]+[ ]+([^ ]+).*$/\1/p')
do
    #este es igual pero para cada sistema de ficheros guarda entre parentesis la 3ra columna y la vuelve a agrupar
        #echo $bloques
        tamano=$(echo -n $bloques | sed -rne '1!s/^[^ ]+[ ]+([^ ]+).*$/\1/p' | wc -m)
        if [[ $bloques > $cifra ]]
        then
            echo $bloques
        fi
done

#[ ]+[^ ]+[ ]+
