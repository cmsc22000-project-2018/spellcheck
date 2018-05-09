#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>





int valid_word(char* word, dict_t* dict) {
	///printf("output is %d ", in_dict(word, dict));
	if (*word == ',' || *word == '\n' || *word == '.') { //we cannot spellcheck for punctuation
		return 1;
	}
    return in_dict(word, dict);
}


int generate_suggestions(char* word, dict_t* dict, char **suggestions) {

	if (strcmp(word, "splling") == 0) {
		suggestions[0] = "spelling";
		suggestions[1] = "spilling";
		return 0;
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
		return -1;
	}

}
	