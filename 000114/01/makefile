CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = test1-1 test1-2 test1-3
SOURCE =  test1-1.o  test1-2.o  test1-3.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) test1-1.o $(SOURCEH) -o test1-1
	$(CXX) $(CXXFLAGS) test1-2.o $(SOURCEH) -o test1-2
	$(CXX) $(CXXFLAGS) test1-3.o $(SOURCEH) -o test1-3

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)