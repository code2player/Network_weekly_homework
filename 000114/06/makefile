CXX = g++
CXXFLAGS = -Wall
RM = rm -f
OBJ = test6-1-1 test6-1-2 test6-2-1 test6-2-2
SOURCE = test6-1-1.o test6-1-2.o test6-2-1.o test6-2-2.o
SOURCEH = ../../common/mydaemon.o ../../common/parameter_process.o
DEF = ../../include/mydaemon.h ../../include/parameter_process.h

all : $(SOURCE) $(SOURCEH) $(DEF)
	$(CXX) $(CXXFLAGS) test6-1-1.o $(SOURCEH) -o test6-1-1
	$(CXX) $(CXXFLAGS) test6-1-2.o $(SOURCEH) -o test6-1-2
	$(CXX) $(CXXFLAGS) test6-2-1.o $(SOURCEH) -o test6-2-1
	$(CXX) $(CXXFLAGS) test6-2-2.o $(SOURCEH) -o test6-2-2

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(SOURCEH) $(OBJ) *.socket