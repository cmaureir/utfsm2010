all:
	pdflatex introduccion.tex
clean:
	rm -f *.{aux,log,out}
	rm -f src/*.aux
x:
	xpdf introduccion.pdf &> /dev/null
o:
	okular introduccion.pdf &> /dev/null
e:
	evince introduccion.pdf &> /dev/null
distclean: clean
	rm -f *.pdf
