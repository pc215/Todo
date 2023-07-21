CC = gcc
CFLAGS = -Wall -Werror -g
LIB = libnode.a
LIBOBJS = node.o
BUILD = libnode.a test_node

.PHONY: all clean

all: $(BUILD)

clean: 
	$(RM) $(BUILD) *.o

test_node: test_node.c node.o

libnode.a: $(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

