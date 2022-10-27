CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = test2-1 test2-2 test2-3 test2-4-1 test2-4-2 test2-5-1 test2-5-2
SOURCE =  test2-1.o  test2-2.o  test2-3.o test2-4-1.o test2-4-2.o test2-5-1.o test2-5-2.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) test2-1.o $(SOURCEH) -o test2-1
	$(CXX) $(CXXFLAGS) test2-2.o $(SOURCEH) -o test2-2
	$(CXX) $(CXXFLAGS) test2-3.o $(SOURCEH) -o test2-3
	$(CXX) $(CXXFLAGS) test2-4-1.o $(SOURCEH) -o test2-4-1
	$(CXX) $(CXXFLAGS) test2-4-2.o $(SOURCEH) -o test2-4-2
	$(CXX) $(CXXFLAGS) test2-5-1.o $(SOURCEH) -o test2-5-1
	$(CXX) $(CXXFLAGS) test2-5-2.o $(SOURCEH) -o test2-5-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ)