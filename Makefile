SHELL = /bin/bash
CC = g++
CPPFLAGS = -std=c++11 -DPREC --coverage
CXXFLAGS = -g -O0 -shared -fPIC

LIBS = -ldl
INCLUDES = -I./include

EXECUTABLE = libobjectpkcs11.so

SRC_DIR = src
INCLUDE_DIR =include
DOC_DIR = docs

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

RM = rm

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS) 
	@echo 'Build complete!'
	@echo ' '

clear_test_files:
	$(MAKE) -C tests veryclean

.PHONY: test
test: all
	$(MAKE) -C tests test

cleantest: clear_test_files test

commitcheck: clean cleantest clean

latex:
	@doxygen object-pkcs11.doxyfile
	$(MAKE) -C docs/latex

clean: 
	$(RM) -f $(SRC_DIR)/*.o
	$(RM) -f $(SRC_DIR)/*.gc*
	$(RM) -f $(EXECUTABLE)
	$(RM) -rf $(DOC_DIR)

