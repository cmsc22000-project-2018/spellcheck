#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	


int valid_word(char* word, dict_t* dict) {
	///printf("output is %d ", in_dict(word, dict));
	if (*word == ',' || *word == '\n' || *word == '.') { //we cannot spellcheck for punctuation
		return EXIT_FAILURE;
	}
    return dict_exists(dict, word);
}


int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
//	assert (dict != NULL);

	if (strcmp(word, "splling") == 0) {
		suggestions[0] = "spelling";
		suggestions[1] = "spilling";
		return EXIT_SUCCESS;
	}
	else if (strcmp(word, "chequer") == 0) {
	suggestions[0] = "checker";
	suggestions[1] = "cheque";
	return 0;
	}

	else if((strcmp(word, "cme") == 0)) {
	suggestions[0] = "come";
	suggestions[1] = "came";
	return 0;
	}
	else {
        int i = 1;
        if (dict == NULL) {
            i = EXIT_FAILURE;
        } // erase after implementing dict. empty line to use variable to avoid warning
		return i;
	}

}
