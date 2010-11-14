NAME=t2
BIN=bin


all:
	@if [ -d bin ];then echo "building..." bin/;else mkdir bin/;fi
	@pdflatex $(NAME).tex
	#BIBINPUTS=. bibtex $(NAME)
	@pdflatex $(NAME).tex
	@pdflatex $(NAME).tex
	@mv $(NAME).pdf bin/

clean:
	@echo "Limpiando..."
	@rm -f $(NAME).{aux,toc,log,bbl,blg,out} portada.aux *~ 

distclean: clean
	@echo "Limpiando todo!..."
	@rm -f $(BIN)/$(NAME).pdf 

x:
	xpdf $(BIN)/$(NAME).pdf &> /dev/null

e:
	evince $(BIN)/$(NAME).pdf &> /dev/null
