src=tarea1

all:
	pdflatex $(src).tex
	pdflatex $(src).tex
	@if [ -d bin ];then mv $(src).pdf bin/;else mkdir bin; mv $(src).pdf bin/;fi

clean:
	rm -f $(src).{aux,log,out}
	rm -f  src/*.{aux,log}
distclean: 
	rm -f $(src).{aux,log,out}
	rm -f  src/*.{aux,log}        	
	rm -f bin/$(src).pdf
x:
	evince -f bin/$(src).pdf
