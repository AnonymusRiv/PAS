#!/bin/bash

echo "1) Sistemas de ficheros cuyo numero de bloques tenga al menos $1 cifras"
df | grep -E "^[^ ]+[[:space:]]+[0-9]{$1}.*"

echo ""
echo "2) Sistemas de ficheros cuyo porcentaje de uso sea inferior al 10%"
df | grep -E "^[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+[0-9]{1}%"

echo ""
echo "3) Sistemas de ficheros cuyo porcentaje de uso sea superior a 90%"
df | grep -E "^[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+[^ ]+[[:space:]]+(90|91|92|93|94|95|96|97|98|99|100)%"