#include "dictionary.h"
#include <stdio.h>
#include <strings.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>	
#include <ctype.h>
#include "suggestion.h"

// checks
int is_in_array(char* word) {
    int num_punctuation = 22;
    char* punctuation_array[] = {"+",",",":"," ",".","-","'","&","!","?",":",";",
                                    "#","~","=","/","$","£","^","\n","_","<",">"};

    int i;
	for (i = 0; i < num_punctuation ; i++) {
		if (strcmp(punctuation_array[i], word) == 0) {
			return 1;
    	}
	}
	return -1;
}

// checks if word is valid -- does not have erroneous punctuations within
	// change to dict_chars_exists?
int word_valid(dict_t* dict, char* word) {
	if (is_in_array(word) == -1 && *word != '\n') {
	    return dict_exists(dict, word);
	}
	else {
		return EXIT_SUCCESS; //automatically assume word is correct as it represents punctuation
	}
    return EXIT_SUCCESS;
}

// helpers for generate_suggestions
//return positive if sth is capitalized
int word_cap_status(char l)
{
	return (!ispunct(l) && l >= 'A' && l <= 'Z');
}

// -1 if not a word 
// 0 if not capitalized
// 1 if first letter is capitalized (note "I" is included here)
// 2 if everything is capitalized
// 3 if inconsistent
int word_check_cap(char* word)
{
	int len = strlen(word);
	int i = 0;
	int npunct = 0;
	while (i < len)
		if (ispunct(word[i])) npunct++; // number of punctuations in word

	if (npunct == len) return -1; // no alphabet in word

	// move to first letter, assuming punctuations like " and '
	while(ispunct(word[i])) i++;

	if (word_cap_status(word[i])) {	// only first word, everything, or inconsistent
		int ncap = 1;	// number of capitalizations
		for (i++ ; i < len; i++)
			if (word_cap_status(word[i])) ncap++;

		if (ncap == 1) return 1;
		if (ncap == len - npunct) return 2;
		return 3;	// inconsistent
	}
	// if control reaches here, then first letter of word is not capitalized
	for (i = 0; i < len; i++)
		if (word_cap_status(word[i])) return 3;

	// if control reaches here, no letters are capitalized
	return 0;
}

// decapitalize letters in a word
char* word_decap(char* word)
{
	int i;
	int len = strlen(word);
	char* decap = strdup(word);

	for (i = 0; i < len; i++)
		if (word_cap_status(word[i])) {
			decap[i] -= 'A' - 'a';
		}
	return decap;
}

// recapitalize
char** word_recap(char** words, int wnum, int flag) // int nsug, int flag)
{
//	switch(flag)
	return words;	// temporary
	/* @firat
	int i = 0;
	while (i < nsug) {
		if () {

		}
	}ssss
	*/
}

// currently hard_coded; generates suggestions for a badly spelled word
int generate_suggestions(dict_t* dict, char* word, char** suggestions, int max_edits, int amount)
{
	if (dict == NULL) {
        suggestions[0] = word; // no change if no dictionary
        return EXIT_FAILURE;
    }

/*
// capitalize, set flag if necessary
    int flag = check_cap(word);
    char* decap_word = word_decap(word);
*/

// get dictionary
    char** sug = suggestion_list(dict, word, max_edits, amount); // change word to decap_word later

// check suggestion number is appropriate
    int i = 0;
    while (sug[i] != NULL) i++;
/*
// recapitalize suggestions if necessary
    if (flag > 0) sug = recap(sug) // nsug, flag); // needs to be loop!
*/

// count number of valid suggestions returned.
// If not requested number, return exit_failure
	if (i < amount) {
		return EXIT_FAILURE;
	}


// copy into suggestions
    for (i = 0; i < amount; i++) {
        suggestions[i] = strdup(sug[i]);
    }

    //free
    int j;
    for (j = 0; j < i; j++)
    	free(sug[j]);
    free(sug);

    return EXIT_SUCCESS;
}
/* note this works, in dev
// currently hard_coded; generates suggestions for a badly spelled word
int generate_suggestions(char* word, dict_t* dict, char **suggestions) {
	if (dict == NULL) { // hard_coded; to change with suggestion.c
        suggestions[0] = word;
    }

	if (strcmp(word, "splling") == 0) {
		suggestions[0] = "spelling";
		suggestions[1] = "spilling";
		return EXIT_SUCCESS;
	} else if (strcmp(word, "chequer") == 0) {
    	suggestions[0] = "checker";
    	suggestions[1] = "cheque";
    	return EXIT_SUCCESS;;
	} else if((strcmp(word, "cme") == 0)) {
    	suggestions[0] = "come";
    	suggestions[1] = "came";
    	return EXIT_SUCCESS;;
	} else if((strcmp(word, "m'y") == 0)) {
        suggestions[0] = "my";
        suggestions[1] = "me";
    }

    return EXIT_FAILURE;
}
*/
