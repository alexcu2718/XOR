# build arguments, its good to use tons of variable for portability.
CC = clang
CFLAGS = -O3 -static
INCLUDE = ./src/include
SRCS = ./src/include/xor.c
TARGET = ./src/main.c
BUILD_LOGFILE = ./build/logs/logs
OUTPUT_DIR = ./build

# make the make build xor instead of exiting without a trace. lazy to put args tho
ifeq ($(MAKECMDGOALS),)
	.DEFAULT_GOAL := xor
endif

# check if the key is the same as the one from the repo to warn the builder tho
# and change it if user gave a 8-bit value via argument.
changeUnsignedCharValue:
	@if [ "$$(grep -E '^\s*unsigned char key' $(TARGET) | sed -n 's/.*=\s*\(0x[0-9A-Fa-f]\+\);.*/\1/p')" = "0xAA" ]; then \
		echo "\033[0;33mmake: Warning: Key value is 0xAA (default).\033[0m"; \
		echo "\033[0;33mmake: Warning: Change it manually or pass KEY=0xNN to make.\033[0m"; \
	fi
	@if [ -z "$(KEY)" ]; then \
		echo "\033[0;33mmake: Warning: KEY not defined, skipping key change.\033[0m"; \
	else \
		if echo "$(KEY)" | grep -Eq '^0x[0-9a-fA-F]{1,2}$$' && [ $$(( $(KEY) )) -le 255 ]; then \
			sed -i 's/^\s*unsigned char key = 0x[0-9A-Fa-f]\+;/unsigned char key = $(KEY);/' $(TARGET); \
			echo "\033[0;32mmake: Info: Key successfully changed to $(KEY).\033[0m"; \
		else \
			echo "\033[0;31mmake: Error: Given key is not a valid 8-bit value.\033[0m"; \
			exit 1; \
		fi; \
	fi

# check the existance of compiler before trying to build.
checkCompilerExistance:
	@command -v $(CC) >/dev/null 2>&1 || { \
	@echo -e "\033[0;31mmake: Error: $(CC) not found. Please install it.\033[0m"; \
	@exit 1; \
	}

# this builds the program after checking the existance of the clang or gcc compiler existance.
xor: changeUnsignedCharValue checkCompilerExistance
	@echo "\e[0;35mmake: Info: Trying to build xor..\e[0;37m"
	@$(CC) $(CFLAGS) -I$(INCLUDE) $(SRCS) $(TARGET) -o $(OUTPUT_DIR)/xor 2>./$(BUILD_LOGFILE) || { \
	@echo -e "\033[0;31mmake: Error: Build failure, check the logs for information. File can be found at $(BUILD_LOGFILE)\033[0m"; \
	@exit 1; \
	}
	@echo "\e[0;36mmake: Info: Build finished without errors, be sure to check logs if concerned. Thank you!\e[0;37m"

# removes the stuff made by compiler and makefile.
clean:
	@rm -f $(BUILD_LOGFILE) $(OUTPUT_DIR)/xor
	@echo "\033[0;32mmake: Info: Clean complete.\033[0m"

.PHONY: xor clean