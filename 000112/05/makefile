CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = tcp_server5-1 tcp_client5-1 tcp_server5-2 tcp_client5-2
SOURCE = tcp_server5-1.o tcp_client5-1.o tcp_server5-2.o tcp_client5-2.o ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(DEF)
	$(CXX) $(CXXFLAGS) tcp_server5-1.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_server5-1
	$(CXX) $(CXXFLAGS) tcp_client5-1.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_client5-1
	$(CXX) $(CXXFLAGS) tcp_server5-2.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_server5-2
	$(CXX) $(CXXFLAGS) tcp_client5-2.o ../../common/mydaemon.o ../../common/parameter_process.o -o tcp_client5-2
	cp -f tcp_client5-1 /mnt/client
	mv /mnt/client/tcp_client5-1 /mnt/client/u1953072_tcp_client5-1
	cp -f tcp_client5-2 /mnt/client
	mv /mnt/client/tcp_client5-2 /mnt/client/u1953072_tcp_client5-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)