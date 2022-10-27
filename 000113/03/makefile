CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server3-1 tcp_client3-1 tcp_server3-2 tcp_client3-2
SOURCE = tcp_server3-1.o tcp_client3-1.o tcp_server3-2.o tcp_client3-2.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o ../../common/tcp_common.o ../../common/socket_common.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h ../../include/tcp_common.h ../../include/socket_common.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server3-1.o $(SOURCEH) -o tcp_server3-1
	$(CXX) $(CXXFLAGS) tcp_client3-1.o $(SOURCEH) -o tcp_client3-1
	$(CXX) $(CXXFLAGS) tcp_server3-2.o $(SOURCEH) -o tcp_server3-2
	$(CXX) $(CXXFLAGS) tcp_client3-2.o $(SOURCEH) -o tcp_client3-2
	cp -f tcp_client3-1 /mnt/client
	mv /mnt/client/tcp_client3-1 /mnt/client/u1953072_tcp_client3-1
	cp -f tcp_client3-2 /mnt/client
	mv /mnt/client/tcp_client3-2 /mnt/client/u1953072_tcp_client3-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)