SRC_DIR   := src
BUILD_DIR := build
EXE 	  := $(BUILD_DIR)/ch
GCC_FLAGS := -O -Wextra -Wall -std=c99 -g # -Werror

SRCS := $(shell find $(SRC_DIR) -name '*.c')
OBJS := $(subst $(SRC_DIR), $(BUILD_DIR), $(SRCS:.c=.o))

all : $(OBJS) $(EXE)

$(EXE) : $(OBJS) | $(BUILD_DIR)
	rm -f $(EXE)
	gcc $(GCC_FLAGS) -o $(EXE) $(OBJS)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | $(BUILD_DIR)
	rm -f $@
	gcc $(GCC_FLAGS) -c -o $@ $<

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

clean:
	rm -rf $(BUILD_DIR)/*

install: all
	sudo mv $(EXE) /usr/local/bin/ch

uninstall:
	sudo rm /usr/local/bin/ch
