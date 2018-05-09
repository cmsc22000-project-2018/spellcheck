# Makefile based on template at https://gist.github.com/xuhdev/1873316

CC = gcc
CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
LDFLAGS = -shared
RM = rm -f
LDLIBS = -lm

SRCS = src/mock_trie.c src/dictionary.c
OBJS = $(SRCS:.c=.o)

.PHONY: all

# $(SRCS:.c=.d):%.d:%.c
# 	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

-include $(SRCS:.c=.d)

.PHONY: clean tests
clean:
	-$(RM) $(LIBS) $(OBJS) $(SRCS:.c=.d)
	make -C ./tests clean

tests: $(OBJS)
	make -C ./tests
