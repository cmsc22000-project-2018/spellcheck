# Makefile based on libgeometry test Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
LDFLAGS = -L./hiredis -Wl,-rpath,./hiredis
RM = rm -f
BIN = test-spellcheck
LDLIBS = -lcriterion -lhiredis

SRCTESTS = test_dictionary.c test_mock_trie.c test_parser.c test_suggestion.c test_word.c test_scfunctions.c test_scfunctions_interactive.c
SRCFILES = ../src/dictionary.c ../src/mock_trie.c ../src/parser.c ../src/suggestion.c ../src/zset_api.c ../src/shellstrings.c ../src/word.c

SRCS = main.c $(SRCTESTS) $(SRCFILES)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(SRCS) -o $(BIN) $(LDLIBS)

clean:
	-$(RM) $(OBJS) $(BIN)
