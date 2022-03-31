#!/bin/bash

echo "1) Usuarios del grupo 46"
echo
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:46"             #busca en el fichero los nombres que cumplen con esa característica
echo
echo "2) Usuarios de los grupos 33,34 o 38"
echo
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[^ ]+:(33|34|38)"
echo
echo "3) Usuarios con un UID de 4 digitos"
echo
cat /etc/passwd|grep -E "^[^ ]+:[^ ]+:[0-9]{4}:"
echo
echo "4) Usuarios con nombres de 4 caracteres"
echo
cat /etc/passwd|grep -E "^[^ :]{4,4}:"