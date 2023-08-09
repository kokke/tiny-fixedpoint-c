BIN_NAME   := fp
CC         := gcc
CC_SAN     := clang
#CC_FLAGS   := -Wall -Wextra -Wundef -Wconversion -O0 -g -std=gnu99
CC_FLAGS   := -Wall -Wextra -Wundef -Wconversion -O3 -std=c99 -march=native
SRC_DIR    := src
OBJ_DIR    := build
BUILD_DIR  := ./build
TEST_DIR   := ./tests
SRC_EXT    := .c
SRC_FILES  := $(shell find $(SRC_DIR) -name "*.c" ! -name "main.c")
OBJ_FILES  := $(addprefix $(OBJ_DIR)/,$(notdir $(SRC_FILES:$(SRC_EXT)=.o)))


.PHONE: all clean test


all: $(OBJ_DIR)/main.o $(BIN_NAME) 

$(OBJ_DIR)/main.o:
	@echo "CC '$(SRC_DIR)/main.c'"
	$(CC) $(CC_FLAGS) -c -o $(OBJ_DIR)/main.o $(SRC_DIR)/main.c
	

$(BIN_NAME): $(OBJ_FILES) $(OBJ_DIR)/main.o
	@echo "LD '$^'"
	$(CC) -o $@ $^ $(CC_FLAGS)


$(BUILD_DIR)/%.o: $(SRC_DIR)/%$(SRC_EXT)
	@echo "CC '$<'"
	$(CC) $(CC_FLAGS) -c -o $@ $<


clean:
	@#echo "Deleting '$(BIN_NAME)' and contents of '$(BUILD_DIR)'"
	rm -rf $(BUILD_DIR)/*
	touch $(BUILD_DIR)/.gitkeep
	rm -f ./$(BIN_NAME)

test: ./$(BIN_NAME)
	(valgrind --version > /dev/null 2>&1 && valgrind -q ./$(BIN_NAME)) || true
	$(CC) $(CC_FLAGS) -I$(SRC_DIR) $(SRC_DIR)/fixedpoint.c -o $(BUILD_DIR)/test_precision $(TEST_DIR)/test_precision.c
	$(BUILD_DIR)/test_precision
	$(CC) $(CC_FLAGS) -I$(SRC_DIR) $(SRC_DIR)/fixedpoint.c -o $(BUILD_DIR)/test_random $(TEST_DIR)/test_random.c -lm
	$(BUILD_DIR)/test_random

