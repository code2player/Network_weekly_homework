CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server4-1 tcp_client4-1 tcp_server4-2 tcp_client4-2
SOURCE = tcp_server4-1.o tcp_client4-1.o tcp_server4-2.o tcp_client4-2.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server4-1.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_server4-1
	$(CXX) $(CXXFLAGS) tcp_client4-1.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_client4-1
	$(CXX) $(CXXFLAGS) tcp_server4-2.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_server4-2
	$(CXX) $(CXXFLAGS) tcp_client4-2.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_client4-2
	cp -f tcp_client4-1 /mnt/client
	mv /mnt/client/tcp_client4-1 /mnt/client/u1953072_tcp_client4-1
	cp -f tcp_client4-2 /mnt/client
	mv /mnt/client/tcp_client4-2 /mnt/client/u1953072_tcp_client4-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)