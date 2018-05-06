.PHONY: clean
CC = gcc
CFLAGS = -O2 -g -Wall -Wextra -I ./include/
HEADS = include/shellstrings.h include/parser.h
SRCS = src/shellstrings.c src/parser.c
TARGET = spellcheck
RM = rm -rf

spellcheck: spellcheck.c include/shellstrings.h include/parser.h src/shellstrings.c src/parser.c
	$(CC) $(CFLAGS) -o $(TARGET) $(SRCS) -lm

clean: $(TARGET)
	$(RM) $(TARGET)
