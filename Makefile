SHELL = /bin/bash
CC = g++
CPPFLAGS = -std=c++11 -DPREC
CXXFLAGS = -g -shared -fPIC

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

.PHONY: test
test: all
	$(MAKE) -C tests test

cleantest: all
	$(MAKE) -C tests clean
	$(MAKE) -C tests test

verycleantest: all
	$(MAKE) -C tests veryclean
	$(MAKE) -C tests test
	

clean: 
	$(RM) -f $(SRC_DIR)/*.o
	$(RM) -f $(EXECUTABLE)
	$(RM) -rf $(DOC_DIR)
