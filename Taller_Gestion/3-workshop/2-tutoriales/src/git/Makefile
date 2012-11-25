CC = gcc
EXE = ssg
CFLAGS = -g -Wall
OBJ = ssg.o plot.o

all: ssg

ssg: $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) -o $(EXE)

plot.o: plot.h
ssg.o: plot.h

clean:
	rm -f *~ *.o
