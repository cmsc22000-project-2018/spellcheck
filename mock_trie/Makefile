all:
	gcc -O2 -Wall -Wextra -g -o mock_trie mock_trie.c mock_main.c
clean:
	rm -f mock_trie

tests:
	gcc -O2 -Wall -Wextra -g -o test_mock_trie test_mock_trie.c mock_main.c mock_trie.c

.PHONY: all clean
