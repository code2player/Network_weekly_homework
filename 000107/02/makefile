CC=gcc
CFLAGS= -Wall
LIBFLAGS= -L. -ltest2
SOURCES= test1.o
LIBSOURCES = libtest2.so
LIBPATH = /usr/lib64/u1953072
OBJ= test2

all : $(SOURCES)
	$(CC) $(CFLAGS) -o $(OBJ) test2.c $(LIBFLAGS) -Wl,-rpath=$(LIBPATH)

dynamic : test1.c
	$(CC) -fPIC -shared test1.c -o $(LIBSOURCES)

install :
	@if [ -d $(LIBPATH) ];\
	then \
		cp $(LIBSOURCES) $(LIBPATH) ;\
	else \
		mkdir $(LIBPATH) ;\
		cp $(LIBSOURCES) $(LIBPATH) ;\
	fi

static : 
	

.PHONY : clean
clean:
	rm -f *.so *.o $(OBJ)

