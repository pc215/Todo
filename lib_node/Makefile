CC = gcc
CFLAGS = -Wall -Werror -g
LIB = libnode.a
LIBOBJS = node.o
BUILD = libnode.a

.PHONY: all clean

all: $(BUILD)

clean: 
	rm $(BUILD) *.o

libnode.a: $(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

