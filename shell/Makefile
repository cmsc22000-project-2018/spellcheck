shell: spellcheck.c src/parser.c src/scfunctions.c src/shellstrings.c
	gcc -fPIC -Wall -Wextra -g -I./include/ -o shell spellcheck.c src/parser.c src/scfunctions.c src/shellstrings.c

test: test.c src/parser.c src/scfunctions.c src/shellstrings.c
	gcc -fPIC -Wall -Wextra -g -I./include/ -o test test.c src/parser.c src/scfunctions.c src/shellstrings.c

clean:
	rm shell test
