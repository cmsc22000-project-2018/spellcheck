CC = gcc
CFLAGS = -fPIC -O2 -g -Wall -Wextra -I./include/
LDFLAGS = -shared
RM = rm -f
TARGET_LIB = libshell.so
LDLIBS = -lm

SRCS = src/shellstrings.c
OBJS := $(SRCS:.c=.o)

.PHONY: all
all: spellcheck

spellcheck: ${TARGET_LIB}

$(TARGET_LIB): $(OBJS)
	$(CC) ${LDFLAGS} -o $@ $^ $(LDLIBS)

$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< >$@

include $(SRCS:.c=.d)

.PHONY: clean
clean:
	-$(RM) $(TARGET_LIB) $(OBJS)
	make -C ./tests clean

tests: ${TARGET_LIB}
	make -C ./tests
