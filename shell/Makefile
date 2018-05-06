CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -fPIC
LIBFLAGS = -shared
DYN_LIBFLAGS = -lshell

HEADS = include/shellstrings.h include/parser.h include/scfunctions.h
SRCS = src/shellstrings.c src/parser.c src/scfunctions.c
OBJS = $(SRCS:.c=.o)

TARGET = spellcheck
TARGET_LIB = libshell.so
RM = rm -f

.PHONY: spellcheck lib
spellcheck: $(TARGET_LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(DYN_LIBFLAGS)

lib: $(OBJS)
	$(CC) $(LIBFLAGS) -o $(TARGET_LIB) $(OBJS)

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) -I ./include/ -c -o $@ $(patsubst %.o,%.c,$@)

.PHONY: clean
clean: $(TARGET)
	$(RM) $(TARGET) $(OBJS) $(TARGET_LIB)
