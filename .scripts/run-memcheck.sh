#!/bin/sh

BIN=$1
EDD=$2
TEST_DIR=$3
TEST_NUM=$4

CYAN='\033[0;36m'
NC='\033[0m'

INPUT_SUBDIR="input"

INPUT_PATH="$TEST_DIR/$EDD/$INPUT_SUBDIR"
OUTPUT_FILE="$(pwd)/output.txt"

if [ -z "$EDD" ]; then
	echo "You need to specify the data structure for memcheck (For example: make memcheck EDD=sll)"
	exit 0
fi

if [ ! -d "$INPUT_PATH" ]; then
	echo "The $INPUT_PATH directory does not exist"
	exit 0
fi

echo -e "\nStarting memcheck with valgrind...\n"

if [ -z "$TEST_NUM" ]; then
	for file in "$INPUT_PATH/"*.txt; do
		echo -e "${CYAN}CHECKING:${NC} $(basename $file)"
		valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=2 $BIN "$EDD" "$file" "$OUTPUT_FILE" > /dev/null
	done

	rm "$OUTPUT_FILE"
else
	INPUT_FILE=$(ls "$INPUT_PATH/$TEST_NUM"*.txt)
	
	echo -e "${CYAN}CHECKING:${NC} $(basename $INPUT_FILE)"

	valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes --log-fd=2 $BIN "$EDD" "$INPUT_FILE" "$OUTPUT_FILE" > /dev/null
	rm "$OUTPUT_FILE"
fi
