#!/bin/bash

if [ $# != 1 ]
then
    echo "Número de argumentos incorrecto. Uso: ./ejercicio6.sh <cifra>"
else
    echo "1) Sistema de ficheros cuyo número de bloques tenga al menos "$1" cifras:"
    df | grep -Eo "^[^ ]+[ ]+[0-9]{$1}.*" | sort
    echo -e "\n2) Sistemas de ficheros cuyo porcentaje de uso sea inferior al 10%:"
    df | grep -Eo "^[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[0-9]{1}%+.*" | sort
    echo -e "\n3) Sistema de ficheros cuyo porcentaje de uso sea de al menos el 90%:"
    df | grep  -Eo "^[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+[^ ]+[ ]+9[0-9]{1}%+.*" | sort
fi


<<'Comment'

if [ $# != 1 ]
then
    echo "Número de argumentos incorrecto. Uso: ./ejercicio6.sh <cifra>"
fi

echo "1) Sistemas de ficheros cuyo numero de bloques tenga al menos $1 cifras"
df | grep -E "^[^ ]+[[:space:]]+[0-9]{$1}.*"

echo ""
echo "2) Sistemas de ficheros cuyo porcentaje de uso sea inferior al 10%"
df | grep -E "^[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+[0-9]{1}%"

echo ""
echo "3) Sistemas de ficheros cuyo porcentaje de uso sea superior a 90%"
df | grep -E "^[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+(90|91|92|93|94|95|96|97|98|99|100)%"
Comment