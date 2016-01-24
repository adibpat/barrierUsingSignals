# Single Author Info:
# abpatwar Aditya B Patwardhan
#

CC = gcc

SRC = mybarrier.c

TEST_SRC = test.c

TEST_OBJ = $(TEST_SRC:.c=.o)

SRC_OBJ = $(SRC:.c=.o)

INCLUDE = mybarrier.h

CFLAGS = -g

.PHONY: all clean test

all: test

%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o *.~ test main

test: $(TEST_OBJ) $(SRC_OBJ) $(INCLUDE)
	$(CC) -pthread -o test $(CFLAGS) $(TEST_OBJ) $(SRC_OBJ)