SRCS=proyecto-gpu

all:
	@rubber -d $(SRCS)
	@mkdir -p bin/
	@mv $(SRCS).pdf bin/
x:
	okular bin/$(SRCS).pdf &> /dev/null & 

clean:
	@echo "limpiando..."
	@rubber --clean $(SRCS)

distclean: clean
	@ echo "borrando PDF..."
	@rm -rf *.pdf bin/*.pdf
