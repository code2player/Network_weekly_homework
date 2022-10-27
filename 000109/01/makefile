CC = g++
CFLAGS = -Wall
RM = rm -f
OBJ = test1-1 test1-2
SOURCE = test1-1.o test1-2.o

all : $(SOURCE)
	$(CC) $(CFLAGS) test1-1.o -o test1-1
	$(CC) $(CFLAGS) test1-2.o -o test1-2

cpnames :
	cp -f test1-1 ../
	cp -f test1-2 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
