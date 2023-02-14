BUILD_DIR=build
BIN=$(BUILD_DIR)/bin


all: $(BUILD_DIR)
	meson compile -C $(BUILD_DIR)

$(BUILD_DIR):
	meson setup $(BUILD_DIR)

run: all
	./$(BIN)	

debug: all
	gdb $(BIN)

clean:
	rm -rf $(BUILD_DIR)
