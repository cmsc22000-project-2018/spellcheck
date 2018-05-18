# Makefile based on template at https://gist.github.com/xuhdev/1873316


CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
RM = rm -f
BIN = spellcheck

SRCS = main.c src/mock_trie.c src/dictionary.c src/parser.c src/word.c src/scfunctions.c src/shellstrings.c
OBJS = $(SRCS:.c=.o)

.PHONY: all tests clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) -o $(BIN) $(SRCS)

tests:
	make -C ./tests

clean:
	-$(RM) $(OBJS) $(BIN)
	make -C ./tests clean
