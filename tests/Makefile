# Makefile based on libgeometry test Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
RM = rm -f
BIN = test-spellcheck
LDLIBS = -lcriterion

#test_word.c in process of construction; add later
TESTSRCS = test_main_functions_interactive.c test_main_functions.c test_dictionary.c test_parser.c test_mock_trie.c
FILESRCS = ../src/dictionary.c ../src/mock_trie.c ../src/parser.c ../src/main_functions.c ../src/shellstrings.c ../src/word.c

SRCS = main.c $(TESTSRCS) $(FILESRCS)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDLIBS)

clean:
	-$(RM) $(OBJS) $(BIN) test_save.txt test_result.txt
