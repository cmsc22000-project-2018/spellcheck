
/*
 * Main function library for the shell
 *
 * See main_functions.h for function documentation.
 */

#include <stdlib.h> 
#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "main_functions.h"
#include "shellstrings.h"
#include "parser.h"
#include "dictionary.h"
#include "word.h"

/* 
 * Order of functions:
 *   I. Saving files
 *   II. Functions for editing strings (lines)
 *   III. Interactive Mode
 *   IV. Batch Mode
 *   V. Main Menu
 */

/*
 * I. Saving Files
 */

/* See main_functions.h */
void save_corrections(char *filename, char **lines) {
    FILE* f = fopen(filename,"w");
    assert(f != NULL);

    int i = 0;
    while (lines[i] != NULL) {
        fprintf(f, "%s", lines[i]); // write lines into file
        i++;
    }

    fclose(f);
}

/* See main_functions.h */
void save_page(char *filename, char **lines, int *quit) {
    int i = 1;
    char line[256];
    char *args = NULL;
    int verify = 0;

    while (i) {
        shell_save();
        shell_prompt();
        i = 0;

        verify = scanf("%s", line);
        
        // Ensures valid input
        assert (!(verify < 0));
        
        // Ensures that string length is within limit
        assert (strlen(line) < 256);

        // Ensures that only one character is entered, otherwise cannot proceed
        if (strlen(line) > 2) {
            shell_error("Please type in one of the indicated commands!");
            i = 1;
        }

        else if (!strcmp(line,"p")) {
        	shell_print(lines);
        	i = 1;
        }

        else if (!strcmp(line, "r")) {
        	*quit = 0;
        }

        // Saves to the same file destination, overwriting existing file
        else if (!strcmp(line, "s")) {
            save_corrections(filename, lines);
            *quit = 1;
        }

        // Either returns to main page, or inputs a new valid destination 
        else if (!strcmp(line, "c")) {  
            while ((args == NULL) ^ i) {
                shell_save_message();

                verify = scanf("%s", line);
                assert (!(verify < 0));

                args = strstr(line, ".txt");
                
                if (!strcmp(line, "r")) {
                    i = 1;
                }
            }

            *quit = 1;

            // Saves to different file destination
            if (i == 0) {
            save_corrections(line, lines);
		    }
        }

        else if (!strcmp(line, "q")) {
			*quit = 1;
		}

        // Wrong input
        else {
			shell_error("Please type in one of the indicated commands!");
			i = 1;
		}
	}
}

/*
 * II. Functions for editing strings (lines)
 */

/* See main_functions.h */
void underline_misspelled(char *word, char *underline) {
    for (int i = 0; i < strlen(word); i++) {
        strcat(underline, "^");
    }

    strcat(underline, " ");
}

/* See main_functions.h */
void underline_correct_spelling(char *word, char *underline) {
    for (int i = 0; i < strlen(word); i++) {
        strcat(underline, " ");
    }

    strcat(underline, " ");
}

/* See main_functions.h */
char *underline_misspelled_sentence(char **misspelled, char *sentence, char *underline) {
    underline[0] = '\0';
    int element = 0;

    while(misspelled[element] != NULL) {
        char *ptr = strstr(sentence, misspelled[element]);

        if (ptr != NULL) {
            for (int i = 0; i < ptr - sentence; i++) {
				strcat(underline, " ");
            }

            for (size_t j = 0; j < strlen(misspelled[element]); j++) {
                strcat(underline, "^");
            }

            sentence = ptr + strlen(misspelled[element]);
        }

        element++;
    }

    return underline;
}

/* See main_functions.h */
int add_to_misspelled(char *word, char **misspelled) {
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

/* See main_functions.h */
int is_in_punct_array(char letter) {
    char punctuation_array[] = {'+', ',', ' ', '.', '-', '\'', '&', '!', '?',
                                ':', ';', '#', '~', '=', '/', '$', '^', '\n',
                                '_', '<', '>', '\"', '\\'};

    int num_punctuation = sizeof(punctuation_array) / sizeof(punctuation_array[0]);

    for (int i = 0; i < num_punctuation; i++) {
        if ((punctuation_array[i] - letter) == 0) {  
            return EXIT_SUCCESS;
        }
    }

    return EXIT_FAILURE;
}

/* See main_functions.h */
int remove_prefix_punctuation(char *word) {
    char prefix_char;
    prefix_char = word[0];

    while (is_in_punct_array(prefix_char) == EXIT_SUCCESS) {
        memmove(word, word + 1, strlen(word)); 
        prefix_char = word[0];
    }
    
    // Removed prefix punctuation 
    return EXIT_SUCCESS;
}

/* See main_functions.h */
int remove_trailing_punctuation(char *word) {
    char trailing_char;

    trailing_char = word[(strlen(word) - 1)];

    while (is_in_punct_array(trailing_char) == EXIT_SUCCESS) {
        word[strlen(word) - 1] = '\0';

        // Checks next trailing character
        trailing_char = word[strlen(word) - 1];
    }

    // Removed trailing punctuation 
    return EXIT_SUCCESS;
}

/* See main_functions.h */
char *remove_punctuation(char *word) {
    char *shaved_word = (char *)malloc(strlen(word));
    
    strcpy(shaved_word, word);
    remove_prefix_punctuation(shaved_word);
    remove_trailing_punctuation(shaved_word);

    // Removed trailing and prefix punctuation without modifying the original word
    return shaved_word;
}


/* See main_functions.h */
int parse_string(char *string, dict_t *dict, char *underline, char **misspelled) {
    char *string_copy = strdup(string);

    // Words are only separated by spaces and newline
    char *tkn = strtok(string," \n");

    while (tkn != NULL) {
        char *shaved_word = remove_punctuation(tkn);

        if (word_valid(dict, shaved_word) == EXIT_FAILURE) {
            add_to_misspelled(shaved_word, misspelled);
        }

        else {        
            printf("error processing text");
            return EXIT_FAILURE;
        }

        // Space and \n are the only delimeters
        tkn = strtok(NULL," \n");
    }

    underline_misspelled_sentence(misspelled, string_copy, underline);
    
    return EXIT_SUCCESS;
}


/* See main_functions.h */
char *correct_line(char *line, char *old_word, char *new_word) {
	char buffer[2000] = {0};
	char *insert_point = &buffer[0];
	char *tmp = line;
	int old_length = strlen(old_word);
	int new_length = strlen(new_word);

	while (1) {
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

/*
 * III. Interactive Mode
 */

char *edit_interactive(char *line, dict_t *dict, int linenumber, int returnflag) {
    char *line_copy = strdup(line);
    int max_no_suggestions = 2; //should the user decide this?
    int length = strlen(line);
    char **misspelled; //generates an empty array where the misspelled words in a line will be stored
    misspelled = calloc(length, sizeof(char*));
    if (misspelled == NULL) {
    	fprintf(stderr,"edit_interactive: calloc failed");
    	exit(0);
    }

    char *underline = (char *)malloc(sizeof(char) * strlen(line + 1)); //generate an empty array where the underline will go
    underline[0] = '\0';

    parse_string(line, dict, underline, misspelled); //identify misspelled words and add to misspelled
    //add to underline function 

    if (misspelled[0] != NULL) shell_interactive_line_print(linenumber, line_copy, underline, returnflag);

    char *suggestions[max_no_suggestions + 1]; //generates empty array where suggestions will be filled
    suggestions[max_no_suggestions] = NULL;

    int i = 0;

    //replacing words according to user suggestions
    while (misspelled[i] != NULL) {
    	int rc = generate_suggestions(misspelled[i], dict, suggestions);

        shell_interactive_replacements(misspelled[i], suggestions, rc);

        char choice[10];
        int check = 0;

        while (!check) {
    		shell_prompt();
        	check = scanf("%s", choice);

        	if (!(choice[0] == 's') && !(choice[0] == 'd') && !(choice[0] == 'i')
        		&& !(isdigit(choice[0]) && (atoi(&choice[0]) <= max_no_suggestions))) {

                shell_error("Please enter a valid input");
                check = 0;
        	} else {
        		check = 1;
        	}
        }

        if (choice[0] == 'd') {	// delete
        	correct_line(line_copy, misspelled[i], "");

         	printf(BOLDWHITE "%s" RESET, line_copy);
            /* if the line is the last line being edited, the last character is
             * EOF, not \n. */
            if(returnflag) printf("\n"); // ,           
         	printf(BOLDRED "%s" RESET, underline_misspelled_sentence(misspelled, line_copy, underline));

        } else if (choice[0] == 's') { // skip
        	// print the edited line
        	printf(BOLDWHITE "%s" RESET, line_copy);
        	/* if the line is the last line being edited, the last character is
        	 * EOF, not \n. */
        	if(returnflag) printf("\n"); // ,
         	printf(BOLDRED "%s" RESET, underline_misspelled_sentence(misspelled, line_copy, underline));

        } else if (choice[0] == 'i') { // insert
        	char c[50];
        	char sig[10];
	        int userconsent = 0;
		    int insertcheck = 0;

        	while (!userconsent) {
	        	printf("\nEnter replacement: ");
		        insertcheck = scanf("%s", c);

    	    	while (insertcheck < 0) {
        			shell_error("\n\nPlease enter a valid input!\n");
        			shell_prompt();
        			insertcheck = scanf("%s\n", c);
        		}

        		printf("Are you sure you wish to replace \"%s\" with \"%s\"? [y, n] : ", misspelled[i], c);
                userconsent = scanf("%s", sig);
                if (sig[0] == 'y') {
                    userconsent = 1;
                } else {
                    userconsent = 0;
                }
        	}

        	char* newword = strdup(c);
        	printf("\nReplacing \"%s\" with \"%s\". \n", misspelled[i], newword);
        	correct_line(line_copy, misspelled[i], newword); //modifies line function

         	printf(BOLDWHITE "%s" RESET, line_copy);
            /* if the line is the last line being edited, the last character is
             * EOF, not \n. */
            if (returnflag) printf("\n");
         	printf(BOLDRED "%s" RESET, underline_misspelled_sentence(misspelled, line_copy, underline));
        } else if (isdigit(choice[0]) && (atoi(&choice[0]) <= max_no_suggestions)) { // choose suggestion
        	// Replace misspelled word with chosen replacement
        	int c = atoi(&choice[0]) - 1;
        	printf("\nReplacing %s with %s.\n\n", misspelled[i], suggestions[c]);
        	correct_line(line_copy, misspelled[i], suggestions[c]); //modifies line function

         	printf(BOLDWHITE "%s\n" RESET, line_copy);
            if (returnflag) printf("\n");
         	printf(BOLDRED "%s" RESET, underline_misspelled_sentence(misspelled, line_copy, underline));
        }
        i++;	// added loop changer
    }

	return line_copy;
}

/* See main_functions.h */
char **interactive_mode(char *filename, dict_t *dict, int *quit) {
	char** lines;
	lines = parse_file(filename);

	// step through phases
	int i = 0;
	int flag = 0;
	int linenumber;

	while (lines[i] != NULL) {
		linenumber = i+1;
		if (lines[i+1] == NULL) flag = 1;	// last line
		lines[i] = edit_interactive(lines[i], dict, linenumber, flag);
		i++;
	}

    *quit = 0;
	return lines;
}
/* 
	IV. Batch Mode
 */

// Adapted from edit_interactive
// returns corrections to a list that contains misspelled words, or returns a corrected char** string
// that can represent an array
/* See main_functions.h */
char *edit_batch(char *line, dict_t *dict, int verbosity, int lnum) {
	char *line_copy = strdup(line);
    int max_no_suggestions = 2; //should the user decide this?
    int length = strlen(line);
    char **misspelled; //generates an empty array where the misspelled words in a line will be stored

    misspelled = calloc(length, sizeof(char*));
    if (misspelled == NULL) {
    	fprintf(stderr,"edit_interactive: calloc failed");
    	exit(0);
    }

    char *underline = (char *)malloc(sizeof(char) * strlen(line + 1)); //generate an empty array where the underline will go
    underline[0] = '\0';

    parse_string(line, dict, underline, misspelled); //identify misspelled words and add to misspelled
    char *suggestions[max_no_suggestions + 1]; //generates empty array where suggestions will be filled
    suggestions[max_no_suggestions] = NULL;

    int i = 0;
    //replacing words, printing out if batch mode
    while (misspelled[i] != NULL) {
        int rc = generate_suggestions(misspelled[i], dict, suggestions);
	    if (rc == EXIT_FAILURE) {
            if (verbosity) suggestions[0] = "No suggestions generated"; 
            if (!verbosity) suggestions[0] = misspelled[i];
            suggestions[1] = NULL;
        }

    	if (!verbosity) {   // in quiet mode, edit the file
            correct_line(line_copy, misspelled[i], suggestions[0]);
        }

	    if (verbosity) shell_verbose_chart(lnum, misspelled[i], suggestions);

	    i++;
	}

	return line_copy;
}

/* See main_functions.h */
char **batch_mode(char *filename, dict_t *dict, int *quit, int verbosity) {
	if (verbosity) printf("\n");

	char** lines;
	lines = parse_file(filename);
	// if lineparse_file returns NULL
	if (lines == NULL) {
		shell_error("file parsing error: check txt file");
		*quit=1;
		return NULL;
	}

	if (verbosity) printf("LINE\t\t\tWORD\t\t\tSUGGESTIONS\n");

	int i=0;
	while (lines[i] != NULL) {
		lines[i] = edit_batch(lines[i], dict, verbosity, i + 1);
		i++;
	}
	return lines;
}

/*
 *  V. Main Page
 */

/* See main_functions.h */
void help_page() {
    shell_help();
	shell_prompt();

	parse_read_line(); // accept any input in the command line
}

/* See main_functions.h */
int fileexists(const char *filename) {
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

/* See main_functions.h */
int change_mode(char *arg) {
	int a = atoi(arg);
    if ((a == 1) | (a == 2) | (a == 3)) {
        return a;
	} else {
        shell_error("Input invalid: return to mode 3, interactive mode");		
	    return 3; 		// default is 3, given this function is only called in main_page, at which point interactive is probably what user intended
    }
    return 3;
}

/* See main_functions.h */
void main_page(char *filename, char *dict, int *quit, int *mode) {
	char* line;
	char** args;

	while (!(*quit)) {
		shell_main_menu();
		shell_prompt();

		line = parse_read_line();
		args = parse_split_line(line);	// line is now split into tokens

		if (args == NULL || args [2] != NULL) { // 3 inputs, or no input: error message
			shell_error("Please type in one of the indicated commands!");
			*quit = 0;

		} else if (!strcmp(args[0],"h")) { // Print help page, then wait for user input
			help_page();
			*quit = 0;

		} else if (!strcmp(args[0],"f")) { // Check valid file path, then exit. If not, redo loop

			if(!fileexists(args[1])) {	//file path checking
				shell_error("Please enter a valid file path for a new edit target!");
				*quit = 0;
			} else {
			strcpy(filename,args[1]);
			printf("\n\nInput file is now %s\n",filename);
			*quit=1;
			}

		} else if (!strcmp(args[0],"d")) {	// dictionary name change 

			if(!fileexists(args[1])) {	// Check file path validity for dicitonary
				shell_error("Please enter a valid file path for a new dictionary!");
				*quit = 0;
			} else {
			strcpy(dict, args[1]);
			printf("\n\nDictionary file is now %s\n", dict);
			*quit = 0;
			}

		} else if (!strcmp(args[0],"q")) { // quit
			*quit = 2;

		} else if (!strcmp(args[0], "m")) { // change mode
			printf("Mode number accepted: %d\n",atoi(args[1]));
            *mode = change_mode(args[1]);
			if(!fileexists(filename)) {
				*quit = 0;
			} else {
				*quit = 1;
			}

		} else { // input bad
			shell_error("Please type in one of the indicated commands!");
			*quit = 0;
		}

		free(line);
		free(args);
	}
}
