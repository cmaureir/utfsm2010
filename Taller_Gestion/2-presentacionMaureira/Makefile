NAME=presentacion
BIN=bin

FLAGS=-output-directory $(BIN)

DEPENDENCIES=$(NAME).tex



all:
	rubber --pdf $(NAME)

clean:
	rubber --pdf --clean $(NAME)

x:
	@xpdf $(NAME).pdf &> /dev/null


e:
	@evince $(NAME).pdf &> /dev/null
