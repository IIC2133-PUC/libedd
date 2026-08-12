# Compiler config
CC=gcc
CFLAGS=-std=gnu11 -Wunused -Wall -g -O0
LIB=-lc -lm

# Directories
SRC=src
OBJ=obj
SOBJ=libedd
BIN=tester

# Testing config
SCRIPTS=scripts
TESTS=tests
TEST_OUTPUTS=outputs
EDD=
TEST_NUM=

# Sources
SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
SOBJS=$(patsubst $(SRC)/lib%.c, $(SOBJ)/lib%.so, $(SRCS))

# Apple M Series support (i detest apple, thanks to Andrew Kelley and the Zig team for zig cc,
# it simplified cross-compilation A LOT (skill issues moment))
APPLE_CC=zig cc
APPLE_CFLAGS=$(CFLAGS) -target aarch64-macos -fno-sanitize=undefined
APPLE_LIB=-lc -lm
SOBJ_APPLE=libedd_apple
# We know that the correct extension would be `.dylib`, this is for consistency and simplicity only
SOBJS_APPLE=$(patsubst $(SRC)/lib%.c, $(SOBJ_APPLE)/lib%.so, $(SRCS))

all: $(BIN)
	@echo "finished compilation"

clean:
	@if [ -d ./$(OBJ) ]; then rm -rf ./$(OBJ); fi
	@if [ -d ./$(SOBJ) ]; then rm -rf ./$(SOBJ); fi
	@if [ -d ./$(SOBJ_APPLE) ]; then rm -rf ./$(SOBJ_APPLE); fi
	@if [ -d ./$(TEST_OUTPUTS) ]; then rm -rf ./$(TEST_OUTPUTS); fi
	@if [ -f ./$(BIN) ]; then rm -f ./$(BIN); fi
	@echo "finished cleaning"

init_objs:
	@if [ ! -d ./$(OBJ) ]; then mkdir ./$(OBJ); fi

init_sobjs:
	@if [ ! -d ./$(SOBJ) ]; then mkdir ./$(SOBJ); fi

init_sobjs_apple:
	@if [ ! -d ./$(SOBJ_APPLE) ]; then mkdir ./$(SOBJ_APPLE); fi

init_test_outputs:
	@if [ ! -d ./$(TEST_OUTPUTS) ]; then mkdir ./$(TEST_OUTPUTS); fi

test: init_test_outputs $(BIN)
	./$(SCRIPTS)/run-tests.sh ./$(BIN) ./$(TESTS) ./$(TEST_OUTPUTS) $(EDD) $(TEST_NUM)

$(BIN): init_objs $(OBJS)
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $@

libedd: init_sobjs $(SOBJS)
	@cp $(SRC)/*.h ./$(SOBJ)

libedd_apple: init_sobjs_apple $(SOBJS_APPLE)
	@cp $(SRC)/*.h ./$(SOBJ_APPLE)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(LIB) -c $< -o $@

$(SOBJ)/lib%.so: $(SRC)/lib%.c
	$(CC) $(CFLAGS) $(LIB) -fPIC -shared -c $< -o $@

$(SOBJ_APPLE)/lib%.so: $(SRC)/lib%.c
	$(APPLE_CC) $(APPLE_CFLAGS) $(APPLE_LIB) -fPIC -shared -c $< -o $@
