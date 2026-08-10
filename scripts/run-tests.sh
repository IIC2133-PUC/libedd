#!/bin/sh

BIN=$1
EDD=$4
TEST_DIR=$2
TEST_OUTPUT_DIR=$3
TEST_NUM=$5

INPUT_SUBDIR="input"
OUTPUT_SUBDIR="output"

INPUT_PATH="$TEST_DIR/$EDD/$INPUT_SUBDIR"
OUTPUT_PATH="$TEST_DIR/$EDD/$OUTPUT_SUBDIR"
TEST_OUTPUT_PATH="$TEST_OUTPUT_DIR/$EDD"

check_output() {
	EXPECTED_OUTPUT=$1
	RESULTED_OUTPUT=$2

	RED='\033[0;31m'
	YELLOW='\033[0;33m'
	GREEN='\033[0;32m'
	NC='\033[0m'

	if [ ! -f "$EXPECTED_OUTPUT" ] || [ ! -f "$RESULTED_OUTPUT" ]; then
		echo -e "[${YELLOW}NOFILE${NC}] $OUTPUT_FILE"
	else
		OUTPUT_FILE=$(basename "$EXPECTED_OUTPUT")

		diff -b "$EXPECTED_OUTPUT" "$RESULTED_OUTPUT" > "${RESULTED_OUTPUT%.*}.diff"
		
		if [ $? -ne 0 ]; then
		    echo -e "[${RED}FAILED${NC}] $OUTPUT_FILE"
		else
		    echo -e "[${GREEN}PASSED${NC}] $OUTPUT_FILE"
		fi
	fi
}

if [ -z "$EDD" ]; then
	echo "You need to specify the data structure to test (For example: make test EDD=sll)"
	exit 0
fi

if [ ! -d "$INPUT_PATH" ]; then
	echo "The $INPUT_PATH directory does not exist"
	exit 0
fi

if [ ! -d "$OUTPUT_PATH" ]; then
	echo "The $OUTPUT_PATH directory does not exist"
	exit 0
fi

if [ ! -d "$TEST_OUTPUT_PATH" ]; then
	mkdir -p "$TEST_OUTPUT_PATH"
fi


if [ -z "$TEST_NUM" ]; then
	for file in "$INPUT_PATH/"*.txt; do
		OUTPUT_FILE=$(basename "$file")

		$BIN "$file" "$EDD" | cat > "$TEST_OUTPUT_PATH/$OUTPUT_FILE"

		check_output "$OUTPUT_PATH/$OUTPUT_FILE" "$TEST_OUTPUT_PATH/$OUTPUT_FILE"
	done
else
	INPUT_FILE=$(ls "$INPUT_PATH/$TEST_NUM"*.txt)
	OUTPUT_FILE=$(basename "$INPUT_FILE")

	echo -e "\n=== ($INPUT_FILE): TEST START ===\n"
	$BIN "$INPUT_FILE" "$EDD" | tee "$TEST_OUTPUT_PATH/$OUTPUT_FILE"
	echo -e "=== ($INPUT_FILE): TEST END   ===\n"

	check_output "$OUTPUT_PATH/$OUTPUT_FILE" "$TEST_OUTPUT_PATH/$OUTPUT_FILE"
fi
