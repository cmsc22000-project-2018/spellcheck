# Makefile based on template at https://gist.github.com/xuhdev/1873316


CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
RM = rm -f
BIN = spellcheck

SRCS = main.c src/mock_trie.c src/dictionary.c src/parser.c src/word.c src/scfunctions.c
OBJS = $(SRCS:.c=.o)

.PHONY: all
all: $(BIN)

$(BIN):
	$(CC) $(CFLAGS) -o $(BIN) $(SRCS)

.PHONY: clean
clean:
	-$(RM) $(OBJS) $(BIN)
