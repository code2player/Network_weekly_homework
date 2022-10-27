COMPILE = c++
CFLAGS = -c -Wall
RM = rm -f
OBJ = test
SOURCE = test1.o test2.o test3.o
DEF = test.h

build : $(SOURCE)
	$(COMPILE) $(SOURCE) -o $(OBJ)

$(SOURCE) : %.o: %.cpp $(DEF)
	$(COMPILE) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)