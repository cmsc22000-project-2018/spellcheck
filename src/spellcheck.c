#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"
#include "scfunctions.h"
#include "shellstrings.h"
#include "dictionary.h"
#include "mock_trie.h"

/* Main function */
int main(int argc, char **argv)
{
	dict_t* dic=dict_new();
	int v = dict_init(dic);
	if (v==1) return 1;

	if (argc == 2 || argc > 4) {
		usage();
		return 0;
	}

	if (argc == 1) {
		greet();
		int* quit = (int*) malloc(sizeof(int));
		*quit = 0;
		while(!(*quit)) {
			main_page(dic,quit);
		}
		free(quit);
	}

	if (argc == 3 || argc ==4) { // batch mode
		batch_mode(argc,argv);
	}

	free(dic);
	return 0;
}
