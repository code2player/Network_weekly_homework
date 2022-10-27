CC = g++
CXXFLAGS = $$(mysql_config --cflags)
RM = rm -f
OBJ = test8-1 test8-2
SOURCE = test8.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE)
	$(CC) $(CXXFLAGS) test8.o ../../common/mydaemon.o ../../common/parameter_process.o -o test8-1 $$(mysql_config --libs) 
	$(CC) $(CXXFLAGS) test8.o ../../common/mydaemon.o ../../common/parameter_process.o -o test8-2 -static  -Wall -L. -lmariadbclient -lssl -lcrypto -pthread -ldl -lz 

cpnames :
	cp -f test8-1 ../
	cp -f test8-2 ../

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
