# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -shared
RM = rm -f
LDLIBS = -lm
BIN = spellcheck

SRCS = src/spellcheck.c src/parser.c src/shellstrings.c src/dictionary.c src/mock_trie.c
OBJS = $(SRCS:.c=.o)

.PHONY: all

$(BIN): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) -o $(BIN) $(LDLIBS) 

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

.PHONY: clean tests
clean:
	-${RM} ${LIBS} ${OBJS} $(SRCS:.c=.d)
	make -C ./tests clean

tests: $(OBJS)
	make -C ./tests
