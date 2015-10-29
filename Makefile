CC = g++
CPPFLAGS = -DGTEST_HAS_PTHREAD=0 -DDEBUG -DPREC
CXXFLAGS = -g -std=c++11

LIBS = -ldl
INCLUDES = -I./include

EXECUTABLE = run.out

SRC_DIR = src
INCLUDE_DIR =include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

RM = /usr/bin/rm

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(LIBS) $(OBJS) 
	@echo 'Build complete!'
	@echo ' '

clean: 
	$(RM) $(SRC_DIR)/*.o
	$(RM) $(EXECUTABLE)
