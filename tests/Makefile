# Makefile based on libgeometry test Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
RM = rm -f
BIN = test-spellcheck
LDLIBS = -lcriterion

SRCS = main.c test_dictionary.c test_mock_trie.c test_parser.c test_shellstring.c ../src/dictionary.c ../src/mock_trie.c ../src/parser.c ../src/shellstrings.c ../src/scfunctions.c ../src/word.c
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDLIBS)

clean:
	-$(RM) $(OBJS) $(BIN)
