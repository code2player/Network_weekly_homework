CC=g++
CFLAGS= -Wall
LIBFLAGS= -L. -ltest4
SOURCES= test1.o
LIBSOURCES = libtest4.so
LIBPATH = /usr/lib64/u1953072
OBJ= test2

all : $(SOURCES)
	$(CC) $(CFLAGS) -o $(OBJ) test2.cpp $(LIBFLAGS) -Wl,-rpath=$(LIBPATH)

dynamic : test1.cpp
	$(CC) -fPIC -shared test1.cpp -o $(LIBSOURCES)

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

