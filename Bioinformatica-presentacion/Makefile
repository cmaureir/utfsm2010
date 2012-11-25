#Este es un make
SRC=bio

all:
	@rubber --pdf $(SRC)
	@if [[ ! -d bin ]];then mkdir bin;fi
	@mv $(SRC).pdf bin/

x:
	okular bin/$(SRC).pdf &> /dev/null

clean:
	@echo "limpiando..."
	@rm -rf *.{aux,log,dvi,ps,out,toc,nav,snm,vrb}
	@rm -rf src/*.aux
distclean: clean
	@ echo "borrando PDF..."
	@rm -rf *.pdf bin/*.pdf
