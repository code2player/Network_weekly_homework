CXX=g++
CXXFLAGS= -Wall
LIBFLAGS= -L. -ltest3
SOURCES= test1.o
LIBSOURCES = libtest3.a
OBJ= test2

all : $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(OBJ) test2.cpp $(LIBFLAGS) -static

static : test1.cpp
	$(CXX) -c test1.cpp
	ar rcs $(LIBSOURCES) $(SOURCES)

dynamic : 


install : 


.PHONY : clean
clean:
	rm -f *.o *.a $(OBJ)

