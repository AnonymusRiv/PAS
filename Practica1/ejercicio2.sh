#!/bin/bash

dir="$1"

if [ $# -ne 1 ] || [ ! -s $dir ]
then
    echo "Argumentos incorrecto. Uso: ./ejercicio2.sh <ruta_directorio>"
    exit
fi

echo "Cambiando permisos de directorios..."
echo ""

for x in $(find $dir)
do
    if [ -d $x ]
    then
        echo "$x"
        chmod u+rwx $x
        chmod g+rx-w $x
        chmod o-rwx $x
    fi
done

echo ""
echo ""
echo "Añadiendo permisos de ejecución a scrips..."
echo ""

for x in $(find $dir)
do
    if [ -d $x ]
    then
        for y in $(find $x)
        do
            echo "$y"
            chmod u+rwx $y/*.sh
        done
    fi
done

echo ""
echo ""
echo "Restringiendo permisos de ficheros de claves..."
echo ""

for x in $(find $dir)
do
    if [ -d $x ]
    then
        for y in $(find $x)
        do
            echo "$y"
            chmod u+rwx $y/*.key
            chmod g-rxw $y/*.key
            chmod o-rwx $y/*.key
        done
    fi
done