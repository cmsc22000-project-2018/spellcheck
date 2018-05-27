#include <stdio.h>
#include <stdlib.h>	
#include <unistd.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "main_functions.h"
#include "dictionary.h"
#include "word.h"



/* 
 *	Order of functions:
 *		I. Saving files
 *		II. Functions for editing strings (lines)
 *		III. Interactive Mode
 *		IV. Batch Mode
 *		V. Main Page
 */


/*
 *	I. Saving Files
 */
void save_corrections(char* filename, char** lines)
{
	FILE* f = fopen(filename,"w");
    assert(f != NULL);
	int i = 0;
	while (lines[i] != NULL) {
		fprintf(f, "%s", lines[i]); // write lines into file
		i++;
	}
	fclose(f);
}

void save_page(char* filename, char** lines, int* quit)
{
	int i = 1;
    char line[256];
    char* args = NULL;
    int verify = 0;

	while (i) {
        shell_save();
		shell_prompt();
		i = 0;

        verify = scanf("%s", line);
        assert (!(verify < 0)); // ensure valid input
        assert (strlen(line) < 256); // ensure that string length is within limit

        if (strlen(line) > 2) { // ensure that only one character is entered, otherwise cannot proceed
            shell_error("Please type in one of the indicated commands!");
            i = 1;
        } else if (!strcmp(line,"p")) {
        	shell_print(lines);
        	i = 1;
        } else if (!strcmp(line, "s")) {
			save_corrections(filename, lines);  // save to the same file destination, overwriting existing file
			*quit = 1;
		} else if (!strcmp(line, "c")) {
            
            while ((args == NULL) ^ i) {    // either user returns to main page, or inputs a vaid new destination
                printf("\n\nEnter a viable file name (*.txt), or enter 'r' to return to the save page.\n\n");
                shell_prompt();
                verify = scanf("%s", line);
                assert (!(verify < 0));

                args = strstr(line, ".txt");
                if (!strcmp(line, "r")) i = 1;
            }

            *quit = 1;
            if (i == 0) save_corrections(line, lines);  // save to different file destination

		} else if (!strcmp(line, "r")) {
			*quit = 0;
		} else if (!strcmp(line, "q")) {
			*quit = 1;
		} else {
			shell_error("Please type in one of the indicated commands!");   // wrong input
			i = 1;
		}

	}
}

/*
 *	II. Functions for editing strings
 */

void underline_misspelled(char *word, char* underline)
{
	int j = strlen(word);
    int i;
	for(i = 0; i < j; i++) {
    	strcat(underline, "^");
	}
		strcat(underline, " ");
}

void underline_correct_spelling(char *word, char* underline)
{
	int j = strlen(word);
    int i;
	for(i = 0; i < j; i++) {
    		strcat(underline, " ");
	}
		strcat(underline, " ");

}

char* underline_misspelled_sentence(char** misspelled, char* sentence) {

	char* underline = malloc(strlen(sentence));
	underline[0] = '\0';
	int element = 0;

	while(misspelled[element] != NULL) {

		char *ptr = strstr(sentence, misspelled[element]);
		if(ptr != NULL) {

			int pos = ptr - sentence;
			int i;
			size_t j;

			for(i = 0; i < pos; i++)
				strcat(underline, " ");

            size_t slen = strlen(misspelled[element]);
			for (j = 0; j < slen; j++)
				strcat(underline, "^");

			sentence = ptr+strlen(misspelled[element]);

		}

		element++;

	}

	return underline;

}



int add_to_misspelled(char *word, char** misspelled)
{
	if (word == NULL || misspelled == NULL) {
		return EXIT_FAILURE;
	}
	int i = 0;
	while(misspelled[i] != NULL) {
		i++;
	}
	misspelled[i] = word;
	return EXIT_SUCCESS;
}


int num_punctuation = 21;
char* punctuation_array[] = {"+",","," ",".","-","'","&","!","?",":",";","#","~","=","/","$","£","^","\n","_","<",">"};


int is_in_array(char* punctuation_array[], char* word) {
    for (int i = 0; i < num_punctuation ; i++) {
        printf("comparing %s to %s", word, punctuation_array[i]);
        if (strcmp(punctuation_array[i], word) == 0) {  
            return EXIT_SUCCESS;   }
    }
    printf("exiting");
    return EXIT_FAILURE;
}

int remove_prefix_punctuation(char *word) {
    char prefix_char = malloc(sizeof(char));
    prefix_char = word[0];
     printf(" prefix is %s \n", &prefix_char);

    if (is_in_array(punctuation_array, &prefix_char) == EXIT_SUCCESS) {
        printf("has prefix");
        memmove(word, word+1, strlen(word)); 
        return EXIT_SUCCESS; //shaved off prefix punctuation 
    }
    else {
        printf("no prefix");
    }

}

int remove_trailing_punctuation(char *word) {
    char trailing_char = malloc(sizeof(char));
    trailing_char = word[(strlen(word)-1)];
     printf(" trail is %s \n", &trailing_char);

    if (is_in_array(punctuation_array, &trailing_char) == EXIT_SUCCESS) {
        printf("has trail");
        word[strlen(word)-1] = '\0';
        return EXIT_SUCCESS; //shaved off prefix punctuation 
    }
    else {
        printf("no trail");
    }

}

char* remove_punctuation(char *word) { //removes trailing and prefix punctuation without modifying original word
    char *shaved_word = (char *)malloc(strlen(word));
    printf("remove word is %s \n", word);
    strcpy(shaved_word, word);
    printf("strcpy \n");
    remove_prefix_punctuation(shaved_word);
    printf("prfix \n");
    remove_trailing_punctuation(shaved_word);
    printf("suffix \n");
    return shaved_word;
}
int parse_string(char* string, dict_t *dict, char *underline, char** misspelled)
{
	char *tkn = strtok(string," \n"); //words only separated by spaces and newline
	while (tkn != NULL) {

		char* shaved_word = remove_punctuation(tkn);

		if (valid_word(dict, shaved_word) == EXIT_FAILURE){
			underline_misspelled(tkn, underline);
			add_to_misspelled(shaved_word, misspelled);
		}
		else if (valid_word(dict, shaved_word) == EXIT_SUCCESS) {
			underline_correct_spelling(tkn, underline);
		}
		else {
			printf("error processing text");
			return EXIT_FAILURE;
		}
		tkn = strtok(NULL," \n"); //spaces are the only delimeters
		//strtok(NULL, ":;\t\n ,.-\"!?()<>`*^");
	}
	return EXIT_SUCCESS;
}

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
char* correct_line(char* line, char* old_word, char* new_word)
{
	char buffer[2000] = {0}; //again, we might need to modify our size estimates
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


/*
 *	III. Interactive Mode
 */

char* edit_interactive(char* line, dict_t* dict, int linenumber, int returnflag)
{
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

    if (misspelled[0] != NULL) {
    printf("Line: %d\n", linenumber);
    printf("%s", line_copy);
    if (returnflag) printf("\n");
    printf("%s\n", underline);
    }

    char *suggestions[max_no_suggestions]; //generates empty array where suggestions will be filled
 
    int i = 0;

    //replacing words according to user suggestions
    while (misspelled[i] != NULL) {
    	int rc = generate_suggestions(misspelled[i], dict, suggestions);

    	if (rc == EXIT_FAILURE) {
			suggestions[0] = misspelled[i];	// to avoid error
			suggestions[1] = misspelled[i];
			suggestions[2] = NULL;
			printf("\nNo suggestions have been generated for %s.\n", misspelled[i]);
       		printf("\nd : Delete Word.\n");
       		printf("i : Input Word.\n");
        	printf("s : Skip.\n");

    	} else {
    	    printf("\nPossible replacements for word %s are:\n\n", misspelled[i]);
            int j = 0;
        	while (suggestions[j] != NULL) {
       			printf("%d : %s \n", j + 1, suggestions[j]);
       			j++;
       		}
       		printf("\nd : Delete Word.\n");
       		printf("i : Input Word.\n");
        	printf("s : Skip.\n");
        }
        printf("\n\n");

        char choice[10];
        int check = 0;

        while (!check) {
    		shell_prompt();
        	check = scanf("%s", choice);

        	if (!(choice[0] == 's') && !(choice[0] == 'd') && !(choice[0] == 'i') && !(isdigit(choice[0]) && (atoi(&choice[0]) <= max_no_suggestions))) {
                shell_error("Please enter a valid input");
                check = 0;
        	} else {
        		check = 1;
        	}
        }

        if (choice[0] == 'd') {	// delete

           	printf("\nDeleting %s.\n", misspelled[i]);
        	correct_line(line_copy, misspelled[i], "");

         	printf("%s\n", line_copy);
         	printf("%s", underline_misspelled_sentence(misspelled, line_copy));

        } else if (choice[0] == 's') { // skip

        	printf("\nNo changes made to \"%s\". \n\n", misspelled[i]);

        } else if (choice[0] == 'i') { // insert

        	char c[50];
        	printf("\nEnter your replacement: ");
        	int insertcheck = scanf("%s", c);

        	while (insertcheck < 0) {
        		shell_error("\n\nPlease enter a valid input!\n");
        		shell_prompt();
        		insertcheck = scanf("%s\n", c);
        	}

        	char* newword = strdup(c);
        	printf("\nReplacing %s with %s. \n", misspelled[i], newword);
        	correct_line(line_copy, misspelled[i], newword); //modifies line function

         	printf("%s\n", line_copy);
         	printf("%s", underline_misspelled_sentence(misspelled, line_copy));

        } else if (isdigit(choice[0]) > 0 && (atoi(&choice[0]) <= max_no_suggestions)) { // choose suggestion

        	int c = atoi(&choice[0]) - 1;
        	printf("\nReplacing %s with %s. \n", misspelled[i], suggestions[c]);
        	correct_line(line_copy, misspelled[i], suggestions[c]); //modifies line function

         	printf("%s\n", line_copy);
         	printf("%s", underline_misspelled_sentence(misspelled, line_copy));
        }

        i++;	// added loop changer
    }

	return line_copy;
}


char** interactive_mode(char* filename, dict_t* dict, int* quit)
{
	char** lines;
	lines = parse_file(filename);

	// step through phases
	int i = 0;
	int flag = 0;
	while (lines[i] != NULL) {
		int linenumber = i+1;
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
// Adapted from sarika's edit_interactive
// returns corrections to a list that contains misspelled words, or returns a corrected char** string
// that can represent an array
char* edit_batch(char* line, dict_t* dict, int verbosity, int lnum)
{

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
    char *suggestions[max_no_suggestions]; //generates empty array where suggestions will be filled

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

	    if (verbosity) {        // this is if verbose mode is enacted
	    	shell_verbose_chart(lnum, misspelled[i], suggestions);
        }

	    i++;
	}

	return line_copy;
}

char** batch_mode(char* filename, dict_t* dict, int* quit, int verbosity)
{
	if (verbosity) printf("\n");

	char** lines;
	lines = parse_file(filename);
	// if lineparse_file returns NULL
	if (lines == NULL) {
		shell_error("file parsing error: check txt file");
		*quit=1;
		return lines;
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
	V. Main Page
 */


void help_page()
{
    shell_help();
	shell_prompt();

	parse_read_line();      // accept any input in the command line
}

int fileexists(const char* filename)
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}


int change_mode(char* arg)
{
	int a = atoi(arg);
    if ((a == 1) | (a == 2) | (a == 3)) {
        return a;
	} else {
        shell_error("Input invalid: return to mode 3, interactive mode");		
	    return 3; 		// default is 3, given this function is only called in main_page, at which point interactive is probably what user intended
    }
    return 3;
}

void main_page(int* quit, int *mode, char* file_name, char* dict_name)
{
	char* line;
	char** args;

	while (!(*quit)) {
		shell_intro();
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
			strcpy(file_name,args[1]);
			printf("\n\nInput file is now %s\n\n\n",file_name);
			*quit=1;
			}

		} else if (!strcmp(args[0],"d")) {	// dictionary name change 

			if(!fileexists(args[1])) {	// Check file path validity for dicitonary
				shell_error("Please enter a valid file path for a new dictionary!");
				*quit = 0;
			} else {
			dict_name=args[1];
			printf("\n\nDictionary file is now %s\n\n\n",dict_name);
			*quit = 0;
			}

		} else if (!strcmp(args[0],"q")) { // quit
			*quit = 2;

		} else if (!strcmp(args[0], "m")) { // change mode
			printf("Mode number accepted: %d\n",atoi(args[1]));
            *mode = change_mode(args[1]);
			if(!fileexists(file_name)) {
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
