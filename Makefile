CC      = gcc
LIB_PATH =  lib_node
LIB     = $(LIB_PATH)/libnode.a
CFLAGS  = -Wall -g -I$(LIB_PATH)
BUILD   = todo 

.PHONY : all lib clean

# -I(directory) - where the header files are located
# -L(directory) - where the library is located
# -l(lib_name) - archive name

all: $(BUILD)

todo: $(LIB)

test_support: $(LIB) support.o
	$(CC) $(CFLAGS) $@.c $(LIB) support.o -o $@ -lssl -lcrypto

clean:
	$(RM) $(BUILD) *.o test_support 

