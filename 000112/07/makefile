CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server7-1 tcp_client7-1 tcp_server7-2 tcp_client7-2 tcp_server7-3 tcp_client7-3 \
tcp_server7-4 tcp_client7-4
SOURCE = tcp_server7-1.o tcp_client7-1.o tcp_server7-2.o tcp_client7-2.o tcp_server7-3.o tcp_client7-3.o \
tcp_server7-4.o tcp_client7-4.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o ../../common/tcp_common.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h ../../include/tcp_common.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server7-1.o $(SOURCEH) -o tcp_server7-1
	$(CXX) $(CXXFLAGS) tcp_client7-1.o $(SOURCEH) -o tcp_client7-1
	$(CXX) $(CXXFLAGS) tcp_server7-2.o $(SOURCEH) -o tcp_server7-2
	$(CXX) $(CXXFLAGS) tcp_client7-2.o $(SOURCEH) -o tcp_client7-2
	$(CXX) $(CXXFLAGS) tcp_server7-3.o $(SOURCEH) -o tcp_server7-3
	$(CXX) $(CXXFLAGS) tcp_client7-3.o $(SOURCEH) -o tcp_client7-3
	$(CXX) $(CXXFLAGS) tcp_server7-4.o $(SOURCEH) -o tcp_server7-4
	$(CXX) $(CXXFLAGS) tcp_client7-4.o $(SOURCEH) -o tcp_client7-4
	cp -f tcp_client7-1 /mnt/client
	mv /mnt/client/tcp_client7-1 /mnt/client/u1953072_tcp_client7-1
	cp -f tcp_client7-2 /mnt/client
	mv /mnt/client/tcp_client7-2 /mnt/client/u1953072_tcp_client7-2
	cp -f tcp_client7-3 /mnt/client
	mv /mnt/client/tcp_client7-3 /mnt/client/u1953072_tcp_client7-3
	cp -f tcp_client7-4 /mnt/client
	mv /mnt/client/tcp_client7-4 /mnt/client/u1953072_tcp_client7-4

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)