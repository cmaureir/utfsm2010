SRCS=csp-cs

all:
	rubber -d $(SRCS)
	mkdir -p bin/
	mv $(SRCS).pdf bin/
	rm -rf *.{aux,log,dvi,ps,out,toc,nav,snm,vrb}
	rm -rf src/*.{aux,log,dvi,ps,out,toc,nav,snm,vrb}

x:
	okular bin/$(SRCS).pdf &> /dev/null & 

clean:
	@echo "limpiando..."
	@rm -rf *.{aux,log,dvi,ps,out,toc,nav,snm,vrb}
	@rm -rf src/*.{aux,log,dvi,ps,out,toc,nav,snm,vrb}

distclean: clean
	@ echo "borrando PDF..."
	@rm -rf *.pdf bin/*.pdf
