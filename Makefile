CC=gcc
CFLAGS=-std=gnu11 -Wunused -Wall -g -O0
LIB=-lc

SRC=src
OBJ=obj
SOBJ=libedd
BIN=tester

SCRIPTS=scripts
TESTS=tests
TEST_OUTPUTS=outputs
EDD=
TEST_NUM=

SRCS=$(wildcard $(SRC)/*.c)
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))
SOBJS=$(patsubst $(SRC)/lib%.c, $(SOBJ)/lib%.so, $(SRCS))

all: $(BIN)
	@echo "finished compilation"

clean:
	@if [ -d ./$(OBJ) ]; then rm -rf ./$(OBJ); fi
	@if [ -d ./$(SOBJ) ]; then rm -rf ./$(SOBJ); fi
	@if [ -d ./$(TEST_OUTPUTS) ]; then rm -rf ./$(TEST_OUTPUTS); fi
	@if [ -f ./$(BIN) ]; then rm -f ./$(BIN); fi
	@echo "finished cleaning"

init_objs:
	@if [ ! -d ./$(OBJ) ]; then mkdir ./$(OBJ); fi

init_sobjs:
	@if [ ! -d ./$(SOBJ) ]; then mkdir ./$(SOBJ); fi

init_test_outputs:
	@if [ ! -d ./$(TEST_OUTPUTS) ]; then mkdir ./$(TEST_OUTPUTS); fi

test: init_test_outputs $(BIN)
	./$(SCRIPTS)/run-tests.sh ./$(BIN) ./$(TESTS) ./$(TEST_OUTPUTS) $(EDD) $(TEST_NUM)

$(BIN): init_objs $(OBJS)
	$(CC) $(CFLAGS) $(LIB) $(OBJS) -o $@

libedd: init_sobjs $(SOBJS)
	@cp $(SRC)/*.h ./$(SOBJ)

$(OBJ)/%.o: $(SRC)/%.c
	$(CC) $(CFLAGS) $(LIB) -c $< -o $@ $(LIB)

$(SOBJ)/lib%.so: $(SRC)/lib%.c
	$(CC) $(CFLAGS) $(LIB) -fPIC -shared -c $< -o $@ $(LIB)
