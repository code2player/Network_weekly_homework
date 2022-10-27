CXX = g++
CXXFLAGS = -L /usr/lib64/mysql -lmariadbclient -lssl -lcrypto -pthread -ldl -lz -I /usr/include/mysql
SOURCES = demo.o
OBJ = mysql_demo

all : $(SOURCES)
	$(CXX) $(SOURCES) -o $(OBJ) $(CXXFLAGS) -static

.PHONY : clean
clean:
	rm -f $(SOURCES) $(OBJ)