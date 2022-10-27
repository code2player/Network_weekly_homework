CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = test3-1 test3-2-1 test3-2-2
SOURCE =  test3-1.o  test3-2-1.o  test3-2-2.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) test3-1.o $(SOURCEH) -o test3-1
	$(CXX) $(CXXFLAGS) test3-2-1.o $(SOURCEH) -o test3-2-1
	$(CXX) $(CXXFLAGS) test3-2-2.o $(SOURCEH) -o test3-2-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)