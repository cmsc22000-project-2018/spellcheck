#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"
#include "main_functions_edit.h"

// Given an array of misspelled words, generates an underline
// for an occurence in sentence

/* See main_functions_edit.h */
char *underline_misspelled_sentence(char **misspelled, char *sentence, char *underline) {
	underline[0] = '\0';
	int element = 0;

	while (misspelled[element] != NULL) {
		char *ptr = strstr(sentence, misspelled[element]);
		if (ptr != NULL) {
			int pos = ptr - sentence;
			int i;
			size_t j;

			for (i = 0; i < pos; i++) {
				strcat(underline, " ");
            }

            size_t slen = strlen(misspelled[element]);

			for (j = 0; j < slen; j++) {
				strcat(underline, "^");
            }

			sentence = ptr + strlen(misspelled[element]);
		}

		element++;
	}

	return underline;
}

/* See main_functions_edit.h */
int add_to_misspelled(char *word, char** misspelled) {
	if (word == NULL || misspelled == NULL) {
		return EXIT_FAILURE;
	}

	int i = 0;

	while (misspelled[i] != NULL) {
		i++;
	}

	misspelled[i] = word;

	return EXIT_SUCCESS;
}

/* See main_functions_edit.h */
bool is_in_punct_array(char letter) {
	char punctuation_array[] = "+, .-\'&!?:;#~=/$^\n_<>\"";
	int num_punctuation = sizeof(punctuation_array) / sizeof(punctuation_array[0]);
	int i;

    for (i = 0; i < num_punctuation ; i++) {
        if ((punctuation_array[i] - letter) == 0) {  
            return true;
        }
    }

    return false;
}

/* See main_functions_edit.h */
void remove_prefix_punctuation(char *word) {
    char prefix_char;
    prefix_char = word[0];

    while (is_in_punct_array(prefix_char) == true) {
        memmove(word, word + 1, strlen(word)); 
        prefix_char = word[0];
    }
}

/* See main_functions_edit.h */
void remove_trailing_punctuation(char *word) {
    char trailing_char;
    
    trailing_char = word[(strlen(word) - 1)];

    while (is_in_punct_array(trailing_char) == true) {
        word[strlen(word) - 1] = '\0';
        trailing_char = word[strlen(word) - 1]; //check next trailing character
    }
}

/* See main_functions_edit.h */
char *remove_punctuation(char *word) { //removes trailing and prefix punctuation without modifying original word
    char *shaved_word = (char *)malloc(strlen(word));
    
    strcpy(shaved_word, word);
    remove_prefix_punctuation(shaved_word);
    remove_trailing_punctuation(shaved_word);
    
    return shaved_word;
}

/* See main_functions_edit.h */
void parse_string(char *string, dict_t *dict, char *underline, char **misspelled) {
	char *string_copy = strdup(string);
	char *tkn = strtok(string," \n"); //words only separated by spaces and newline
	
    while (tkn != NULL) {
		char *shaved_word = remove_punctuation(tkn);

		if (word_valid(dict, shaved_word) == EXIT_FAILURE){
			add_to_misspelled(shaved_word, misspelled);
		}

		else if (word_valid(dict, shaved_word) == EXIT_SUCCESS) {
            continue;
		}

		else {
			shell_error("Error processing text", false);
			return;
		}

		tkn = strtok(NULL," \n"); //spaces and \n are the only delimeters
	}

	underline_misspelled_sentence(misspelled, string_copy, underline);
}

/* See main_functions_edit.h */
char *correct_line(char *line, char *old_word, char *new_word) {
	char buffer[2000] = {0}; // Might need to modify the size estimate

	char *insert_point = &buffer[0];
	char *tmp = line;
    
	int old_length = strlen(old_word);
	int new_length = strlen(new_word);

	while(1) {
		char *p = strstr(tmp, old_word);

		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		memcpy(insert_point, new_word, new_length);
		insert_point += new_length;

		tmp = p + old_length;
	}

	strcpy(line, buffer);

	return line;
}