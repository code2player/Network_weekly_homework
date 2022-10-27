COMPILE = clang++
CFLAGS = -c -Wno-invalid-source-encoding -Wno-unused-command-line-argument
RM = rm -f
OBJ = test1 test2 test3
SOURCE = test1.o test2.o test3.o

all : $(SOURCE)
	$(COMPILE)  test1.o -o test1
	$(COMPILE)  test2.o -o test2
	$(COMPILE)  test3.o -o test3

test1 : test1.o
	$(COMPILE)  test1.o -o test1

test2 : test2.o
	$(COMPILE)  test2.o -o test2

test3 : test3.o
	$(COMPILE)  test3.o -o test3

$(SOURCE): %.o: %.cpp
	$(COMPILE) $(CFLAGS) -o $@ $<

.PHONY : clean
clean :
	$(RM) $(SOURCE) $(OBJ)
