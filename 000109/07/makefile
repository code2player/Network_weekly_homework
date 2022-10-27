CC = g++
CFLAGS = -Wall
RM = rm -f
OBJ = test7
SOURCE = test7.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CC) test7.o ../../common/mydaemon.o ../../common/parameter_process.o -o test7
#
#$(SOURCE) : %.o: %.c $(DEF)
#	$(CC) $(CFLAGS) -c -o $@ $<

cpnames :
	cp -f test7 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
