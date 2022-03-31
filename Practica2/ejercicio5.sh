#!/bin/bash

echo "1) Grupos que contengan al menos 1 usuario además del usuario principal del grupo"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:[^ ]+')"
echo
echo "2) Grupos cuyo nombre empiece por u y acabe por s"
echo
echo "$(cat /etc/group | grep -Eo '^u.*s:[^_]:.*$')"                #.[que haya algo]/1
echo
echo "3) Grupos que no contengan ningún usuario adicional"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[^ ]+:$')"          #./1[que haya algo]
echo
echo "4) Grupos con GID menor que 100"
echo
echo "$(cat /etc/group | grep -Eo '^[^ ]+:[^ ]+:[0-9]{2}:.*$')"