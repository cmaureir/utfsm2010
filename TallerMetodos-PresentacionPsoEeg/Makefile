SRCS=pso

all:
	pdflatex $(SRCS).tex
	pdflatex $(SRCS).tex
	mkdir -p bin/
	mv $(SRCS).pdf bin/
	rm -rf *.{aux,log,dvi,ps,out,toc,nav,snm,vrb}
	rm -rf src/*.{aux,log,dvi,ps,out,toc,nav,snm,vrb}

x:
	xpdf bin/$(SRCS).pdf &> /dev/null
e:
	evince bin/$(SRCS).pdf &> /dev/null

clean:
	@echo "limpiando..."
	@rm -rf *.{aux,log,dvi,ps,out,toc,nav,snm,vrb}
	@rm -rf src/*.{aux,log,dvi,ps,out,toc,nav,snm,vrb}

distclean: clean
	@ echo "borrando PDF..."
	@rm -rf *.pdf bin/*.pdf
