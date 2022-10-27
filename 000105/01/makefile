COMPILE = gcc
CFLAGS = -c -Wall
RM = rm -f
OBJ = test
SOURCE = test1.o test2.o test3.o

build : $(SOURCE)
	$(COMPILE) $(SOURCE) -o $(OBJ)

$(SOURCE): %.o: %.c
	$(COMPILE) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
