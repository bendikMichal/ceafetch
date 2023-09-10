

BUILD_DIR := build
SRC_DIR := src

BUILD_CMD := gcc -o $(BUILD_DIR)/cpfetch $(SRC_DIR)/cpfetch.c $(SRC_DIR)/libs/stringEx.c

ifeq ($(OS),Windows_NT)
$(BUILD_DIR)/cpfetch.exe: $(SRC_DIR)/cpfetch.c
	$(BUILD_CMD)
else
$(BUILD_DIR)/cpfetch: $(SRC_DIR)/cpfetch.c
	$(BUILD_CMD)

endif

run:
	@./$(BUILD_DIR)/./cpfetch
