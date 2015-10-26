
CC = g++
CPPFLAGS = -DGTEST_HAS_PTHREAD=0
CXXFLAGS = -g -std=c++11

LIBS = 
INCLUDES = -I/usr/include/pkcs11

EXECUTABLE = run.out

SRC_DIR = src
INCLUDE_DIR =include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.c=.o)


%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBS)
	@echo 'Build complete!'
	@echo ' '

clean: 
	@rm $(SRC_DIR/*.o)
	@rm $(EXECUTABLE)
