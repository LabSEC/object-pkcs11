INCLUDES = -I./$(GTEST_DIR) -I. -I../include
CC = g++
CPPFLAGS = -std=c++11
CXXFLAGS = -g
EXECUTABLE = test.out
LIBS = -pthread -ldl

GTEST_DIR = gtest
SRC_DIR = src
MOCK_DIR = mock
LIBOBJECTPKCS11 = ../libobjectpkcs11.so
MOCKED_SO = pkcs11mocked.so

TEST_SRCS += $(wildcard $(SRC_DIR)/*.cpp)
OBJS += $(TEST_SRCS:.cpp=.o)

%.o: %.cpp
	@echo 'Building file: $<'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -O0 -Wall -c -o "$@" "$<"
	@echo 'Finished building: $<'
	@echo ' '

all: check-lib gtest mocker $(OBJS)
	$(CC) $(CPPFLAGS) $(CXXFLAGS) -o $(EXECUTABLE) $(OBJS) $(LIBOBJECTPKCS11) ./$(GTEST_DIR)/gtest-all.o $(LIBS)
	@echo 'Build complete!'
	@echo ' '

mocker:
	@echo 'Building Mocked PKCS11'
	$(CC) $(CPPFLAGS) $(CXXFLAGS) $(INCLUDES) -shared -fPIC -o $(MOCKED_SO) $(MOCK_DIR)/*.cpp $(LIBS)
	mv $(MOCKED_SO) /tmp
	@echo ' '

check-lib:
	@test -s $(LIBOBJECTPKCS11) || { echo "You should compile/install Object Pkcs11 first!"; exit 1; }
	
gtest: ./$(GTEST_DIR)/gtest-all.o

test:	all
	@echo 'Executing tests...'
	./$(EXECUTABLE)
	@echo 'Done!'

clean:
	rm -rf ./$(SRC_DIR)/*.o $(EXECUTABLE)

veryclean: clean
	rm -rf ./$(GTEST_DIR)/*.o
	rm -f $(MOCKED_SO)


