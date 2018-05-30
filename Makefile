# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -L./api -Wl,-rpath,./api
LDLIBS = -lredisApi
RM = rm -rf
BIN = spellcheck

SRCS = main.c src/dictionary.c src/parser.c src/word.c src/main_functions.c src/shellstrings.c
OBJS = $(SRCS:.c=.o)

.PHONY: all tests clean
all: $(BIN)

$(BIN): $(OBJS)
	make -C api
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS) $(LDLIBS)

tests:
	make -C api
	make -C ./tests

clean:
	-$(RM) $(OBJS) $(BIN) spellcheck.dSYM
	make -C ./tests clean
	make -C api clean
	