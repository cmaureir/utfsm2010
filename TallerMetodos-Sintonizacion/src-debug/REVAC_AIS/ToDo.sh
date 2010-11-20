#nohup ./REVAC ejecutable_algoritmo.sh configuracion.config instancias 1 > Salida-Revac.out &
date
echo "Running 200_01...."
./REVAC ejecutable_algoritmo.sh configuracion.config instancias/pb_200_01.txt 1  > 200_01.out 
date
echo "Running 200_09...."
./REVAC ejecutable_algoritmo.sh configuracion.config instancias/pb_200_09.txt 1  > 200_09.out 
date
echo "Running 200_10...."
./REVAC ejecutable_algoritmo.sh configuracion.config instancias/pb_200_10.txt 1  > 200_10.out 
date
