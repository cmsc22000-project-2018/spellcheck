# Makefile based on libgeometry test Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
LDFLAGS = -L../api -Wl,-rpath,./api
RM = rm -f
BIN = test-spellcheck
LDLIBS = -lcriterion -lredisApi


TESTSRCS = test_main_functions_interactive.c test_word.c test_main_functions.c test_dictionary.c test_parser.c
FILESRCS = ../src/dictionary.c ../src/parser.c ../src/main_functions.c ../src/shellstrings.c ../src/word.c

SRCS = main.c $(TESTSRCS) $(FILESRCS)
OBJS = $(SRCS:.c=.o)

.PHONY: all clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDFLAGS) $(LDLIBS)

clean:
	-$(RM) $(OBJS) $(BIN) test_save.txt test_result.txt *.rdb
