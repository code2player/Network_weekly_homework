CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server4-1 tcp_client4-1 tcp_server4-2 tcp_client4-2 tcp_server4-3 tcp_client4-3 tcp_server4-4 tcp_client4-4
SOURCE = tcp_server4-1.o tcp_client4-1.o tcp_server4-2.o tcp_client4-2.o tcp_server4-3.o tcp_client4-3.o tcp_server4-4.o tcp_client4-4.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o ../../common/tcp_common.o ../../common/socket_common.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h ../../include/tcp_common.h ../../include/socket_common.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server4-1.o $(SOURCEH) -o tcp_server4-1
	$(CXX) $(CXXFLAGS) tcp_client4-1.o $(SOURCEH) -o tcp_client4-1
	$(CXX) $(CXXFLAGS) tcp_server4-2.o $(SOURCEH) -o tcp_server4-2
	$(CXX) $(CXXFLAGS) tcp_client4-2.o $(SOURCEH) -o tcp_client4-2
	$(CXX) $(CXXFLAGS) tcp_server4-3.o $(SOURCEH) -o tcp_server4-3
	$(CXX) $(CXXFLAGS) tcp_client4-3.o $(SOURCEH) -o tcp_client4-3
	$(CXX) $(CXXFLAGS) tcp_server4-4.o $(SOURCEH) -o tcp_server4-4
	$(CXX) $(CXXFLAGS) tcp_client4-4.o $(SOURCEH) -o tcp_client4-4
	cp -f tcp_client4-1 /mnt/client
	mv /mnt/client/tcp_client4-1 /mnt/client/u1953072_tcp_client4-1
	cp -f tcp_client4-2 /mnt/client
	mv /mnt/client/tcp_client4-2 /mnt/client/u1953072_tcp_client4-2
	cp -f tcp_client4-3 /mnt/client
	mv /mnt/client/tcp_client4-3 /mnt/client/u1953072_tcp_client4-3
	cp -f tcp_client4-4 /mnt/client
	mv /mnt/client/tcp_client4-4 /mnt/client/u1953072_tcp_client4-4

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)