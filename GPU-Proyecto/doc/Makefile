src=proyecto

all:
	@rubber -d $(src)
	@rubber --clean $(src)

clean:
	@rubber --clean

distclean: 
	@rm -f $(src).pdf
x:
	@okular $(src).pdf &> /dev/null &
