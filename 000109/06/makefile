CC = g++
CFLAGS = -Wall
RM = rm -f
OBJ = test6
SOURCE = test6.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CC) test6.o ../../common/mydaemon.o ../../common/parameter_process.o -o test6
#
#$(SOURCE) : %.o: %.c $(DEF)
#	$(CC) $(CFLAGS) -c -o $@ $<

cpnames :
	cp -f test6 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
