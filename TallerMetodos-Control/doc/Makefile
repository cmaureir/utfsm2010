src=informe_final

all:
	@rubber -d $(src)
	@if [ -d bin ];then mv $(src).pdf bin/;else mkdir bin; mv $(src).pdf bin/;fi

clean:
	rm -f $(src).{aux,log,bbl,blg,out}
	rm -f  src/*.{aux,log}
distclean: 
	rm -f $(src).{aux,log,bbl,blg,out}
	rm -f  src/*.{aux,log}        	
	rm -f bin/$(src).pdf
x:
	okular bin/$(src).pdf &> /dev/null &
