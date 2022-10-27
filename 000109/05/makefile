CC = g++
CFLAGS = -Wall
RM = rm -f
OBJ = test5
SOURCE = test5.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CC) test5.o ../../common/mydaemon.o ../../common/parameter_process.o -o test5
#
#$(SOURCE) : %.o: %.c $(DEF)
#	$(CC) $(CFLAGS) -c -o $@ $<

cpnames :
	cp -f test5 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
