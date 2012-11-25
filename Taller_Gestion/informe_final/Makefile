src=main

all:
	@rubber -d $(src)
	@mkdir -p bin
	@mv $(src).pdf bin/
	@rubber --clean $(src)

clean:
	@rubber --clean
distclean: 
	rm -f bin/$(src).pdf
	rmdir bin
x:
	okular bin/$(src).pdf &> /dev/null &
