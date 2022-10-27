CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server2 tcp_client2
SOURCE = tcp_server2.o tcp_client2.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server2.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_server2
	$(CXX) $(CXXFLAGS) tcp_client2.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_client2
	cp -f tcp_client2 /mnt/client
	mv /mnt/client/tcp_client2 /mnt/client/u1953072_tcp_client2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)