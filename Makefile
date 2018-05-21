# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -L./hiredis -Wl,-rpath,./hiredis
RM = rm -f
BIN = spellcheck
LDLIBS = -lhiredis

SRCS = main.c src/mock_trie.c src/dictionary.c src/parser.c src/word.c src/main_functions.c src/shellstrings.c src/suggestion.c src/zset_api.c
OBJS = $(SRCS:.c=.o)

.PHONY: all tests clean
all: $(BIN)

$(BIN): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(BIN) $(SRCS) $(LDLIBS) 

tests:
	make -C ./tests

clean:
	-$(RM) $(OBJS) $(BIN) test_save.txt
	make -C ./tests clean
