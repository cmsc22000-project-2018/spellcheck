# Makefile based on libgeometry test Makefile

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I../include/
RM = rm -f
BIN = test-spellcheck
LDLIBS = -lcriterion

SRCS = main.c test_mock_trie.c test_dictionary.c ../src/mock_trie.c ../src/dictionary.c

.PHONY: all
all: ${BIN}

$(BIN):
	$(CC) $(CFLAGS) $(SRCS) -o $(BIN) $(LDLIBS)

.PHONY: clean
clean:
	-$(RM) $(BIN)
