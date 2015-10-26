CC = gcc
CPPFLAGS = -DGTEST_HAS_PTHREAD=0
CXXFLAGS = -g -std=c++11

LIBS = -ldl #-L/usr/lib64/pkcs11/ /usr/lib64/pkcs11/libsofthsm2.so
INCLUDES = -I.

EXECUTABLE = run.out

SRC_DIR = src
INCLUDE_DIR =include

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)


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
	@rm $(SRC_DIR/*.o)
	@rm $(EXECUTABLE)
