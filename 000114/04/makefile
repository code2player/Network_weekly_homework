CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = test4-1 test4-2 test4-3 test4-4-1 test4-4-2 test4-5-1 test4-5-2
SOURCE =  test4-1.o  test4-2.o  test4-3.o test4-4-1.o test4-4-2.o test4-5-1.o test4-5-2.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) test4-1.o $(SOURCEH) -o test4-1
	$(CXX) $(CXXFLAGS) test4-2.o $(SOURCEH) -o test4-2
	$(CXX) $(CXXFLAGS) test4-3.o $(SOURCEH) -o test4-3
	$(CXX) $(CXXFLAGS) test4-4-1.o $(SOURCEH) -o test4-4-1
	$(CXX) $(CXXFLAGS) test4-4-2.o $(SOURCEH) -o test4-4-2
	$(CXX) $(CXXFLAGS) test4-5-1.o $(SOURCEH) -o test4-5-1
	$(CXX) $(CXXFLAGS) test4-5-2.o $(SOURCEH) -o test4-5-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)