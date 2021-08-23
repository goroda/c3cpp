CXX = g++
# CXX = g++-8
CFLAGS = -g -Wall -std=c++11 

LLOC = ..
LIB = c3cpp
INCLUDE = ../c3cpp

TARGET = c3cpp_test

# MAC_FLAGS = -Xlinker -rpath -Xlinker @executable_path/..

$(TARGET): main.o
	$(CXX) -Wl,-R. -o $(TARGET) main.o -L$(LLOC) -l$(LIB) && mv $(TARGET) ../

main.o: main.cpp
	$(CXX) $(CFLAGS) -c main.cpp -I$(INCLUDE)

clean:
	rm -rf *.o *.dSYM 

dist-clean: clean
	rm -rf *~ 
