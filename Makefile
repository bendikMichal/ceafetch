

BUILD_DIR := build
SRC_DIR := src

i_stringEx := -L./$(SRC_DIR)/stringEx -I./$(SRC_DIR)/stringEx -lstringEx
BUILD_CMD := gcc -o $(BUILD_DIR)/ceafetch $(SRC_DIR)/ceafetch.c $(i_stringEx)


ifeq ($(OS),Windows_NT)
$(BUILD_DIR)/ceafetch.exe: $(SRC_DIR)/ceafetch.c $(BUILD_DIR) $(SRC_DIR)/stringEx
	$(BUILD_CMD)
else
$(BUILD_DIR)/ceafetch: $(SRC_DIR)/ceafetch.c $(BUILD_DIR) $(SRC_DIR)/stringEx
	$(BUILD_CMD)

endif

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(SRC_DIR)/stringEx:
	cd $(SRC_DIR) && git clone https://github.com/bendikMichal/stringEx && cd stringEx && make

run:
	@./$(BUILD_DIR)/./ceafetch
