SHELL=/bin/bash
NAME=cronograma
BIN=bin

FLAGS=-output-directory $(BIN)

DEPENDENCIES=$(NAME).tex



all:
	@echo "Generando cronograma por primera vez..."
	@mkdir -p bin
	pdflatex $(FLAGS) $(NAME).tex
	@echo "y por segunda vez..."
	pdflatex $(FLAGS) $(NAME).tex

clean:
	@echo "Limpiando..."
	@rm -f $(BIN)/$(NAME).{aux,toc,log,out,nav,snm}

distclean:
	@echo "Limpiando todo!..."
	@rm -f $(BIN)/$(NAME).{pdf,aux,toc,log,out,nav,snm}

x:
	@xpdf $(BIN)/$(NAME).pdf &> /dev/null


e:
	@evince $(BIN)/$(NAME).pdf &> /dev/null
