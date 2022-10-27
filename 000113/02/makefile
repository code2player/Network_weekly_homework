CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server2-1 tcp_client2-1 tcp_server2-2 tcp_client2-2 tcp_server2-3 tcp_client2-3 tcp_server2-4 tcp_client2-4 \
tcp_server2-5 tcp_client2-5 tcp_server2-6 tcp_client2-6 tcp_server2-7 tcp_client2-7
SOURCE = tcp_server2-1.o tcp_client2-1.o tcp_server2-2.o tcp_client2-2.o tcp_server2-3.o \
tcp_server2-4.o tcp_server2-5.o tcp_client2-5.o tcp_server2-6.o tcp_server2-7.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o ../../common/tcp_common.o ../../common/socket_common.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h ../../include/tcp_common.h ../../include/socket_common.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server2-1.o $(SOURCEH) -o tcp_server2-1
	$(CXX) $(CXXFLAGS) tcp_client2-1.o $(SOURCEH) -o tcp_client2-1
	$(CXX) $(CXXFLAGS) tcp_server2-2.o $(SOURCEH) -o tcp_server2-2
	$(CXX) $(CXXFLAGS) tcp_client2-2.o $(SOURCEH) -o tcp_client2-2
	$(CXX) $(CXXFLAGS) tcp_server2-3.o $(SOURCEH) -o tcp_server2-3
	$(CXX) $(CXXFLAGS) tcp_client2-2.o $(SOURCEH) -o tcp_client2-3
	$(CXX) $(CXXFLAGS) tcp_server2-4.o $(SOURCEH) -o tcp_server2-4
	$(CXX) $(CXXFLAGS) tcp_client2-2.o $(SOURCEH) -o tcp_client2-4
	$(CXX) $(CXXFLAGS) tcp_server2-5.o $(SOURCEH) -o tcp_server2-5
	$(CXX) $(CXXFLAGS) tcp_client2-5.o $(SOURCEH) -o tcp_client2-5
	$(CXX) $(CXXFLAGS) tcp_server2-6.o $(SOURCEH) -o tcp_server2-6
	$(CXX) $(CXXFLAGS) tcp_client2-5.o $(SOURCEH) -o tcp_client2-6
	$(CXX) $(CXXFLAGS) tcp_server2-7.o $(SOURCEH) -o tcp_server2-7
	$(CXX) $(CXXFLAGS) tcp_client2-5.o $(SOURCEH) -o tcp_client2-7
	cp -f tcp_client2-1 /mnt/client
	mv /mnt/client/tcp_client2-1 /mnt/client/u1953072_tcp_client2-1
	cp -f tcp_client2-2 /mnt/client
	mv /mnt/client/tcp_client2-2 /mnt/client/u1953072_tcp_client2-2
	cp -f tcp_client2-3 /mnt/client
	mv /mnt/client/tcp_client2-3 /mnt/client/u1953072_tcp_client2-3
	cp -f tcp_client2-4 /mnt/client
	mv /mnt/client/tcp_client2-4 /mnt/client/u1953072_tcp_client2-4
	cp -f tcp_client2-5 /mnt/client
	mv /mnt/client/tcp_client2-5 /mnt/client/u1953072_tcp_client2-5
	cp -f tcp_client2-6 /mnt/client
	mv /mnt/client/tcp_client2-6 /mnt/client/u1953072_tcp_client2-6
	cp -f tcp_client2-7 /mnt/client
	mv /mnt/client/tcp_client2-7 /mnt/client/u1953072_tcp_client2-7

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)