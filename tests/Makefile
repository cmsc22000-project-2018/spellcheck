# Makefile based on libgeometry test Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
RM = rm -f
BIN = test-spellcheck
LDLIBS = -lcriterion

SHELLTESTSRCS = test_main_functions_batch.c test_main_functions_interactive.c test_main_functions_home.c test_main_functions_save.c
TESTSRCS = test_main_functions_interactive.c test_word.c test_dictionary.c test_parser.c $(SHELLTESTSRCS)
SHELLFILESRCS = ../src/main_functions_home.c ../src/main_functions_save.c ../src/main_functions_interactive.c ../src/main_functions_edit.c ../src/main_functions_batch.c
FILESRCS = ../src/dictionary.c ../src/mock_trie.c ../src/parser.c ../src/shellstrings.c ../src/word.c $(SHELLFILESRCS)

SRCS = main.c $(TESTSRCS) $(FILESRCS)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDLIBS)

clean:
	-$(RM) $(OBJS) $(BIN) test_save.txt test_result.txt
