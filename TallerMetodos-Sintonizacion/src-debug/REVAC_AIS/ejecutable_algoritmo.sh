#!/bin/bash

#if [ $# -lt 5 ]; then
#  echo "Cantidad invalida de parametros";
#  exit -1
#fi

input_filename=$1
output_filename=$2
rm -rf ${output_filename}
seed=$3

shift 3

#echo $@

#repeticiones=1
#tiempo_max=0
#iteraciones=200
#tripw=0
#repw=0
#sini=1
#fact_mut=0
#res=1
#ord=0
#rl=0
#rep_size=10
#tasa_reem=0.2
#fp_trip=0.5
#fp_rep=0.5


TASA_CL=0
FACT_CL=0
TASA_RP=0

while [ $# != 0 ]; do
    flag="$1"
    case "$flag" in
	-TASA_CL) if [ $# -gt 1 ]; then
              arg="$2"
              shift
	      TASA_CL=$arg
            fi
            ;;
	-FACT_CL) if [ $# -gt 1 ]; then
              arg="$2"
              shift
	      FACT_CL=$arg
            fi
            ;;
	-TASA_RP) if [ $# -gt 1 ]; then
              arg="$2"
              shift
	      TASA_RP=$arg
            fi
            ;;
        *) echo "Unrecognized flag or argument: $flag"
            ;;
        esac
    shift
done

#linea de codigo a especificar
for archivo in $( ls $input_filename |grep .txt); do
	echo "./csp ${input_filename} ${FACT_CL} ${TASA_CL} ${TASA_RP}"
	./csp ${input_filename} ${FACT_CL} ${TASA_CL} ${TASA_RP}
done



