# Makefile de ejemplo para latex
#
# all: Compilacion del archivo tex
# clean: Eliminamos los archivos generado en la compilacion
# distclean: Eliminamos el PDF generado

all:
	pdflatex informe.tex
clean:
	rm -f *.{aux,log}
	rm -f src/*.aux
x:
	xpdf informe.pdf &> /dev/null
o:
	okular informe.pdf &> /dev/null
e:
	evince informe.pdf &> /dev/null
distclean: clean
	rm -f *.pdf
