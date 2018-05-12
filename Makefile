# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -shared
RM = rm -f

# We'll need these when we have something beyond a testing binary
SRCS = src/mock_trie.c src/dictionary.c
OBJS = $(SRCS:.c=.o)

.PHONY: all

.PHONY: clean tests
clean:
	-$(RM) $(OBJS) $(LIBS)
	make -C ./tests clean

tests:
	make -C ./tests
