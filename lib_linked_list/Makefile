CC     ?= gcc
CFLAGS ?= -Wall -Werror -Wextra -g \
					-I../lib_node/
LDLIBS = -L../lib_node/ -lnode
LIB = liblinkedlist.a
LIBOBJS = linked_list.o
BUILD = libnode test_linked_list $(LIB) 

.PHONY: all clean

all: $(BUILD)

libnode: 
	cd ../lib_node; make libnode.a

liblinkedlist.a: $(LIBOBJS)
	ar rcs $(LIB) $(LIBOBJS)

linked_list.o: libnode

test_linked_list: test_linked_list.c linked_list.o

clean:
	$(RM) $(BUILD) *.o core
	cd ../lib_node/; make clean;
	
