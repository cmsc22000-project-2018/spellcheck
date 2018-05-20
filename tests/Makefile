# Makefile based on libgeometry test Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
RM = rm -f
BIN = test-spellcheck
LDLIBS = -lcriterion


SRCS = main.c test_main_functions_interactive.c test_word.c test_main_functions.c test_dictionary.c test_parser.c ../src/dictionary.c ../src/mock_trie.c ../src/parser.c ../src/scfunctions.c ../src/shellstrings.c ../src/word.c

OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDLIBS)

clean:
	-$(RM) $(OBJS) $(BIN)
