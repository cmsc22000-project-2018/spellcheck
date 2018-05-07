shell: src/word.c src/mock_trie.c spellcheck.c src/dictionary.c src/parser.c src/scfunctions.c src/shellstrings.c
	gcc -fPIC -Wall -Wextra -g -I./include/ -o shell spellcheck.c src/parser.c src/scfunctions.c src/shellstrings.c src/dictionary.c src/mock_trie.c src/word.c

test: test.c src/parser.c src/scfunctions.c src/shellstrings.c 
	gcc -fPIC -Wall -Wextra -g -I./include/ -o test test.c src/parser.c src/scfunctions.c src/shellstrings.c

clean:
	rm shell test
