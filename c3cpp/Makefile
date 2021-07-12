CXX = g++-8
# CC = gcc
CFLAGS = -g -Wall -O3 -std=c++11 -fPIC

LLOC = ../../c3/build/c3 
LIB = c3

TARGET = libc3cpp.so

LALOC = /System/Library/Frameworks/Accelerate.framework/Versions/A/Frameworks/vecLib.framework/Versions/A
# BLAS = libBLAS.dylib
# LAPACK = libLAPACK.dylib
BLAS = BLAS
LAPACK = LAPACK

# temp : main.o function_train.o approx_opts.o functions.o utils.o 
# 	$(CXX) $(CFLAGS) -o $(TARGET) main.o function_train.o approx_opts.o utils.o -L$(LLOC) -l$(LIB)

# main.o: main.cpp
# 	$(CXX) $(CFLAGS) -c main.cpp

MAC_NAME=libc3cpp.so
# MAC_INSTALL= -dynamiclib -install_name @rpath../$(MAC_NAME) -o $(MAC_NAME)
UNIX_INSTALL = -shared -o $(MAC_NAME)

lib : function_train.o approx_opts.o functions.o utils.o 
	$(CXX)  $(CFLAGS) function_train.o functions.o approx_opts.o utils.o -L$(LLOC) -l$(LIB) -L$(LALOC) -l$(BLAS) -l$(LAPACK) $(UNIX_INSTALL) && cp $(MAC_NAME) ../

function_train.o: 
	$(CXX) $(CFLAGS) -c function_train.cpp 

approx_opts.o: 
	$(CXX) $(CFLAGS) -c approx_opts.cpp 

functions.o: 
	$(CXX) $(CFLAGS) -c functions.cpp 

utils.o: 
	$(CXX) $(CFLAGS) -c utils.cpp 

clean:
	rm -rf *.o *.dSYM *.so

dist-clean: clean
	rm -rf *~ 
