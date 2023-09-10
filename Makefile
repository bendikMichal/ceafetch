

BUILD_DIR := build
SRC_DIR := src

ifeq ($(OS),Windows_NT)
$(BUILD_DIR)/cpfetch.exe: $(SRC_DIR)/cpfetch.c
	gcc -o $(BUILD_DIR)/cpfetch $(SRC_DIR)/cpfetch.c

else
$(BUILD_DIR)/cpfetch: $(SRC_DIR)/cpfetch.c
	gcc -o $(BUILD_DIR)/cpfetch $(SRC_DIR)/cpfetch.c

endif

run:
	@./$(BUILD_DIR)/./cpfetch
