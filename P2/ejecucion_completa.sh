#!/bin/bash

RUTA_EJECUTABLE="./bin/practica2"
RUTA_ARCHIVOS_ENTRADA="/home/juanma/GitHub/MH/P2/datos_MDD"
RUTA_ARCHIVO_SALIDA="/home/juanma/Escritorio/Uni/Segundo_Cuatri/MH/P2/datos.txt"

iteraciones=0
total_iteraciones=50

echo ""
rm $RUTA_ARCHIVO_SALIDA
	
for FILE in $(ls $RUTA_ARCHIVOS_ENTRADA)
do	
	iteraciones=$((iteraciones+1))
	echo "Comienza la iteracion" $iteraciones "de" $total_iteraciones
	$RUTA_EJECUTABLE $RUTA_ARCHIVOS_ENTRADA/$FILE >> $RUTA_ARCHIVO_SALIDA
done
