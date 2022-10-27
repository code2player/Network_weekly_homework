CC = g++
CFLAGS = -Wall
RM = rm -f
OBJ = test3-1 test3-2
SOURCE = test3-1.o test3-2.o ../../common/mydaemon.o
DEF = ../../include/mydaemon.h

all : $(SOURCE) $(DEF)
	$(CC) test3-1.o ../../common/mydaemon.o -o test3-1
	$(CC) test3-2.o ../../common/mydaemon.o -o test3-2
#
#$(SOURCE) : %.o: %.c $(DEF)
#	$(CC) $(CFLAGS) -c -o $@ $<

cpnames :
	cp -f test3-1 ../
	cp -f test3-2 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
