CC = g++
CPPFLAGS = -DGTEST_HAS_PTHREAD=0 -DDEBUG -DPREC
CXXFLAGS = -g -std=c++11

LIBS = -ldl
INCLUDES = -I./include

EXECUTABLE = run.out
EXECUTABLE_SRC = main.cpp
EXECUTABLE_OBJ = $(EXECUTABLE_SRC:.cpp=.o)

SRC_DIR = src
INCLUDE_DIR =include
TEST_DIR = tests

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
SRCS_TEST = $(wildcard $(TEST_DIR)/*.cpp)
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

MOCKED_SO = tests/pkcs11mocked.so

RM = /usr/bin/rm

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS) $(EXECUTABLE_OBJ)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(LIBS) $(OBJS) $(EXECUTABLE_OBJ)
	@echo 'Build complete!'
	@echo ' '

$(MOCKED_SO):
	@echo 'Building Mocked PKCS11'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -shared -fPIC -o $(MOCKED_SO) $(LIBS) tests/mock/*.cpp
	@echo ' '

test: $(OBJS) $(OBJS_TEST) $(MOCKED_SO)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o test.out $(LIBS) $(OBJS) $(OBJS_TEST) -lgtest
	@echo 'Test build complete!'
	@echo ' '

clean: 
	$(RM) $(SRC_DIR)/*.o
	$(RM) $(TEST_DIR)/*.o
	$(RM) $(EXECUTABLE)
	$(RM) $(MOCKED_SO)
