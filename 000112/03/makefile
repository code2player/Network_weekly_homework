CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server3 tcp_client3
SOURCE = tcp_server3.o tcp_client3.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server3.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_server3
	$(CXX) $(CXXFLAGS) tcp_client3.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_client3
	cp -f tcp_client3 /mnt/client
	mv /mnt/client/tcp_client3 /mnt/client/u1953072_tcp_client3

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)