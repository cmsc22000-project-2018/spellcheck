# Makefile based on template at https://gist.github.com/xuhdev/1873316
spellcheck: main.c src/parser.c src/scfunctions.c src/shellstrings.c src/dictionary.c src/word.c src/mock_trie.c
	gcc -fPIC -Wall -Wextra -g -I./include/ -o spellcheck main.c src/parser.c src/scfunctions.c src/shellstrings.c src/word.c src/dictionary.c src/mock_trie.c

clean: spellcheck
	rm -f spellcheck

#CC = gcc
#CFLAGS = -fPIC -Wall -Wextra -O2 -g -I./include/
#LDFLAGS = -shared
#RM = rm -f
#LDLIBS = -lm

#SRCS = src/dictionary.c src/mock_trie.c
#OBJS = $(SRCS:.c=.o)

#.PHONY: all

#$(SRCS:.c=.d):%.d:%.c
	$(CC) $(CFLAGS) -MM $< -MT $(patsubst %.d,%.o,$@) > $@

#-include $(SRCS:.c=.d)

#.PHONY: clean tests
#clean:
#	-${RM} ${LIBS} ${OBJS} $(SRCS:.c=.d)
#	make -C ./tests clean

#tests: $(OBJS)
#	make -C ./tests
