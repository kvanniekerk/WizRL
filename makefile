CC      := gcc
CFLAGS  := -std=c11 -Wall -Wextra -O2
LDLIBS  := -lm

BIN     := bin
SHARED  := include/game_math.c include/filehandler.c
HEADERS := $(wildcard include/*.h)

.PHONY: all run test clean prerequisites

all: $(BIN)/main

# Only rebuilds when a source or header has changed.
# The "| $(BIN)" means bin/ must exist first, but its timestamp is ignored.
$(BIN)/main: main.c $(SHARED) $(HEADERS) | $(BIN)
	$(CC) $(CFLAGS) main.c $(SHARED) -o $@ -lncurses $(LDLIBS)

$(BIN)/test: test.c $(SHARED) $(HEADERS) | $(BIN)
	$(CC) $(CFLAGS) test.c $(SHARED) -o $@ $(LDLIBS)

# -p: no error if bin/ already exists
$(BIN):
	mkdir -p $(BIN)

run: $(BIN)/main
	./$(BIN)/main

test: $(BIN)/test
	./$(BIN)/test

# -f: no error if bin/ is already gone
clean:
	rm -rf $(BIN)

prerequisites:
	sudo pacman -S --needed ncurses
