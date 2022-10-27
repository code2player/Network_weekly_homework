CC = g++
CFLAGS = -Wall
RM = rm -f
OBJ = test4-1 test4-2
SOURCE = test4-1.o test4-2.o ../../common/mydaemon.o
DEF = ../../include/mydaemon.h

all : $(SOURCE) $(DEF)
	$(CC) test4-1.o ../../common/mydaemon.o -o test4-1
	$(CC) test4-2.o ../../common/mydaemon.o -o test4-2
#
#$(SOURCE) : %.o: %.c $(DEF)
#	$(CC) $(CFLAGS) -c -o $@ $<

cpnames :
	cp -f test4-1 ../
	cp -f test4-2 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
