SHELL = /bin/bash
CC = g++
CPPFLAGS = -DGTEST_HAS_PTHREAD=0 -DDEBUG -DPREC
CXXFLAGS = -g -std=c++11

LIBS = -ldl -lgtest -lpthread
INCLUDES = -I./include

EXECUTABLE = run.out
EXECUTABLE_SRC = main.cpp
EXECUTABLE_OBJ = $(EXECUTABLE_SRC:.cpp=.o)
TEST_EXECUTABLE = test.out

SRC_DIR = src
INCLUDE_DIR =include
TEST_DIR = tests
DOC_DIR = docs

SRCS = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)
SRCS_TEST = $(wildcard $(TEST_DIR)/*.cpp)
OBJS_TEST = $(SRCS_TEST:.cpp=.o)

MOCKED_SO = tests/pkcs11mocked.so

RM = rm

%.o: %.cpp
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Compiler'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS) $(EXECUTABLE_OBJ)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $(EXECUTABLE) $(OBJS) $(EXECUTABLE_OBJ) $(LIBS) 
	@echo 'Build complete!'
	@echo ' '

$(MOCKED_SO):
	@echo 'Building Mocked PKCS11'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -shared -fPIC -o $(MOCKED_SO) tests/mock/*.cpp $(LIBS) 
	@echo ' '

test: $(OBJS) $(OBJS_TEST) $(MOCKED_SO)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -o $(TEST_EXECUTABLE) $(OBJS) $(OBJS_TEST) $(LIBS) 
	@echo 'Test build complete!'
	@echo ' '

clean: 
	$(RM) -f $(SRC_DIR)/*.o
	$(RM) -f $(TEST_DIR)/*.o
	$(RM) -f $(EXECUTABLE)
	$(RM) -f $(MOCKED_SO)
	$(RM) -f $(TEST_EXECUTABLE)
	$(RM) -rf $(DOC_DIR)

run: 	all
	./$(EXECUTABLE)


runtest: all test
	./$(TEST_EXECUTABLE)
