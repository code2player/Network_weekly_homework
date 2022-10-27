CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = test5-1 test5-2-1 test5-2-2
SOURCE =  test5-1.o  test5-2-1.o  test5-2-2.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) test5-1.o $(SOURCEH) -o test5-1
	$(CXX) $(CXXFLAGS) test5-2-1.o $(SOURCEH) -o test5-2-1
	$(CXX) $(CXXFLAGS) test5-2-2.o $(SOURCEH) -o test5-2-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)