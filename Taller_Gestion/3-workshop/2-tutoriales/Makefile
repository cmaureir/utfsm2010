SHELL=/bin/bash
NAME=tutorial
BIN=bin

FLAGS=-output-directory $(BIN)

DEPENDENCIES=$(NAME).tex



all: trac planner latex git skype

trac:
	@mkdir -p bin
	pdflatex $(FLAGS) $(NAME)_trac.tex

planner:
	@mkdir -p bin
	pdflatex $(FLAGS) $(NAME)_planner.tex

latex:
	@mkdir -p bin
	pdflatex $(FLAGS) $(NAME)_latex.tex

git:
	@mkdir -p bin
	pdflatex $(FLAGS) $(NAME)_git.tex

skype:
	@mkdir -p bin
	pdflatex $(FLAGS) $(NAME)_skype.tex

clean:
	@echo "Limpiando..."
	@rm -f $(BIN)/$(NAME)_trac.{aux,toc,log,out,nav,snm}
	@rm -f $(BIN)/$(NAME)_planner.{aux,toc,log,out,nav,snm}
	@rm -f $(BIN)/$(NAME)_latex.{aux,toc,log,out,nav,snm}
	@rm -f $(BIN)/$(NAME)_git.{aux,toc,log,out,nav,snm}
