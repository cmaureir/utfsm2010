SRCS=main
BIN=bin

FLAGS=-output-directory $(BIN)

DEPENDENCIES=$(SRCS).tex

all:
	mkdir -p bin
	rm -f $(BIN)/$(SRCS).{aux,bbl,blg}
	pdflatex $(FLAGS) $(SRCS).tex
#	BIBINPUTS=. bibtex $(BIN)/$(SRCS)
	pdflatex $(FLAGS) $(SRCS).tex
	pdflatex $(FLAGS) $(SRCS).tex

clean:
	rm -f $(SRCS).{aux,bbl,blg,log,dvi,ps,out,snm,toc,nav} *~
	rm -f $(BIN)/$(SRCS).{aux,log,bbl,blg}
distclean: clean
	rm -f $(BIN)/$(SRCS).{pdf}
x:
	xpdf $(BIN)/$(SRCS).pdf
e:
	evince $(BIN)/$(SRCS).pdf
