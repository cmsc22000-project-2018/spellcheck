CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -fPIC -Wl,-rpath,../shell
LIBFLAGS = -shared
DYN_LIBFLAGS = libshell.so

HEADS = include/shellstrings.h include/parser.h include/scfunctions.h
SRCS = src/shellstrings.c src/parser.c src/scfunctions.c
OBJS = $(SRCS:.c=.o)
MAIN = spellcheck.c
MAINOBJ = $(MAIN:.c=.o)

TARGET = spellcheck
TARGET_LIB = libshell.so
RM = rm -f

.PHONY: spellcheck lib
spellcheck: $(MAIN) $(TARGET_LIB)
	$(CC) $(CFLAGS) -o $(TARGET) $(MAIN) $(DYN_LIBFLAGS)

$(TARGET_LIB): $(OBJS)
	$(CC) $(LIBFLAGS) -o $(TARGET_LIB) $(OBJS)

$(OBJS): %.o:%.c
	$(CC) $(CFLAGS) -I ./include/ -c -o $@ $(patsubst %.o,%.c,$@)

.PHONY: clean
clean: $(OBJS)
	$(RM) $(TARGET) $(TARGET_LIB) $(OBJS) $(MAINOBJ)
