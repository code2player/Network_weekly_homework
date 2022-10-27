CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server6-1 tcp_client6-1 tcp_server6-2 tcp_client6-2 tcp_server6-3 tcp_client6-3 \
tcp_server6-4 tcp_client6-4 tcp_server6-5 tcp_client6-5
SOURCE = tcp_server6-1.o tcp_client6-1.o tcp_server6-2.o tcp_client6-2.o tcp_server6-3.o tcp_client6-3.o \
tcp_server6-4.o tcp_client6-4.o tcp_server6-5.o tcp_client6-5.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o ../../common/tcp_common.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h ../../include/tcp_common.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server6-1.o $(SOURCEH) -o tcp_server6-1
	$(CXX) $(CXXFLAGS) tcp_client6-1.o $(SOURCEH) -o tcp_client6-1
	$(CXX) $(CXXFLAGS) tcp_server6-2.o $(SOURCEH) -o tcp_server6-2
	$(CXX) $(CXXFLAGS) tcp_client6-2.o $(SOURCEH) -o tcp_client6-2
	$(CXX) $(CXXFLAGS) tcp_server6-3.o $(SOURCEH) -o tcp_server6-3
	$(CXX) $(CXXFLAGS) tcp_client6-3.o $(SOURCEH) -o tcp_client6-3
	$(CXX) $(CXXFLAGS) tcp_server6-4.o $(SOURCEH) -o tcp_server6-4
	$(CXX) $(CXXFLAGS) tcp_client6-4.o $(SOURCEH) -o tcp_client6-4
	$(CXX) $(CXXFLAGS) tcp_server6-5.o $(SOURCEH) -o tcp_server6-5
	$(CXX) $(CXXFLAGS) tcp_client6-5.o $(SOURCEH) -o tcp_client6-5
	cp -f tcp_client6-1 /mnt/client
	mv /mnt/client/tcp_client6-1 /mnt/client/u1953072_tcp_client6-1
	cp -f tcp_client6-2 /mnt/client
	mv /mnt/client/tcp_client6-2 /mnt/client/u1953072_tcp_client6-2
	cp -f tcp_client6-3 /mnt/client
	mv /mnt/client/tcp_client6-3 /mnt/client/u1953072_tcp_client6-3
	cp -f tcp_client6-4 /mnt/client
	mv /mnt/client/tcp_client6-4 /mnt/client/u1953072_tcp_client6-4
	cp -f tcp_client6-5 /mnt/client
	mv /mnt/client/tcp_client6-5 /mnt/client/u1953072_tcp_client6-5

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)