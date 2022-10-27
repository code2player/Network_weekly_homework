CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server1 tcp_client1
SOURCE = tcp_server1.o tcp_client1.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server1.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_server1
	$(CXX) $(CXXFLAGS) tcp_client1.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_client1
	cp -f tcp_client1 /mnt/client
	mv /mnt/client/tcp_client1 /mnt/client/u1953072_tcp_client1

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)