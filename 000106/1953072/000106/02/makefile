CC=g++
CFLAGS= -Wall
SOURCES= test.o
OBJ= test

all : $(SOURCES)
	$(CC) $(CFLAGS) $(SOURCES) -o $(OBJ) -static

.PHONY : clean
clean:
	rm -f $(SOURCES) $(OBJ)
