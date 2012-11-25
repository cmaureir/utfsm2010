all:
	pdflatex ssg.tex
clean:
	rm -f *.{aux,log}
	rm -f src/*.aux
x:
	xpdf ssg.pdf &> /dev/null
o:
	okular ssg.pdf &> /dev/null
e:
	evince ssg.pdf &> /dev/null
distclean: clean
	rm -f *.pdf
