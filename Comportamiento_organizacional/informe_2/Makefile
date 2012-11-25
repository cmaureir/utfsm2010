SHELL=/bin/bash
NAME=informe
BIN=bin

DEPENDENCIES=$(NAME).tex



all:
	@if [ -d bin ];then echo "building..." bin/;else mkdir bin/;fi
	@pdflatex $(NAME).tex
	BIBINPUTS=. bibtex $(NAME)
	@pdflatex $(NAME).tex
	@pdflatex $(NAME).tex
	@mv $(NAME).pdf bin/

clean:
	@echo "Limpiando..."
	@rm -f $(NAME).{aux,toc,log,bbl,blg} portada.aux 

distclean:
	@echo "Limpiando todo!..."
	@rm -f $(NAME).{pdf,aux,toc,log,bbl,blg} portada.aux 

x:
	xpdf $(BIN)/$(NAME).pdf &> /dev/null

e:
	evince $(BIN)/$(NAME).pdf &> /dev/null
