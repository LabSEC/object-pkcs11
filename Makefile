
CC = gcc
LIBS = 

EXECUTABLE = run.out

SRC_DIR = src

SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(SRCS:.c=.o)


%.o: %.c
	@echo 'Building file: $<'
	@echo 'Invoking: GCC Compiler'
	$(CC) -O0 -Wall -c -o "$@" "$<" $(LIBS)
	@echo 'Finished building: $<'
	@echo ' '

all: $(OBJS)
	$(CC) -o $(EXECUTABLE) $(OBJS) $(LIBS)
	@echo 'Build complete!'
	@echo ' '

clean: 
	@rm $(SRC_DIR/*.o)
	@rm $(EXECUTABLE)
