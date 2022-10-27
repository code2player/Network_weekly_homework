CC = g++
CFLAGS = -Wall
RM = rm -f
OBJ = test2
SOURCE = test2.o ../../common/mydaemon.o
DEF = ../../include/mydaemon.h

all : $(SOURCE)
	$(CC) test2.o ../../common/mydaemon.o -o test2

cpnames :
	cp -f test2 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
