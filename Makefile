# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/ -I./lib/
LDFLAGS = -L./api -Wl,-rpath,./lib/api
LDLIBS = -lredisApi
RM = rm -rf
BIN = spellcheck

SHELLSRCS = src/main_functions_batch.c src/main_functions_interactive.c src/main_functions_save.c src/main_functions_edit.c src/main_functions_home.c
SRCS = main.c src/dictionary.c src/parser.c src/word.c src/shellstrings.c lib/log.c/src/log.c $(SHELLSRCS)
OBJS = $(SRCS:.c=.o)

.PHONY: all tests clean
all: $(BIN)

$(BIN): $(OBJS)
	make -C api
	$(CC) $(CFLAGS) $(OBJS) -o $(BIN) $(LDFLAGS) $(LDLIBS)

tests:
	make -C ./lib/api
	make -C ./tests

clean:
	-$(RM) $(OBJS) $(BIN) spellcheck.dSYM *.rdb
	make -C ./tests clean
	make -C ./lib/api clean
	