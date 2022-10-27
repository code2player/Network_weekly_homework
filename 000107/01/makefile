CC=g++
CFLAGS= -Wall
LIBFLAGS= -L. -ltest1
SOURCES= test1.o
LIBSOURCES = libtest1.a
OBJ= test2

all : $(SOURCES)
	$(CC) $(CFLAGS) -o $(OBJ) test2.c $(LIBFLAGS) -static

static : test1.c
	$(CC) -c test1.c
	ar rcs $(LIBSOURCES) $(SOURCES)

dynamic : 
	

install : 


.PHONY : clean
clean:
	rm -f *.o $(LIBSOURCES) $(OBJ)

