#include <stdio.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "scfunctions.h"
#include "dictionary.h"
#include "word.h"
#include <stdlib.h>	


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
// Accet a filename and an array of strings, then write that array into the file
void save_corrections(char* filename, char** lines)
{
	FILE* f = fopen(filename,"w");
    assert(f != NULL);
	int i = 0;
	while (lines[i] != NULL) {
		fprintf(f, "%s", lines[i]);
		i++;
	}
	fclose(f);
}

// operates save_page
void save_page(char* filename, char** lines, int* quit)
{
	int i = 1;
    char line[256];
    char* args = NULL;
    int verify = 0;

// save shell
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

// produces a set of underlines for the misspelled word
void underline_misspelled(char *tkn, char* underline)
{
	int j = strlen(tkn);
    int i = 0;
	for(; i < j; i++) {
    	strcat(underline, "^");
	}
		strcat(underline, " ");
		// printf("start \n");
		// printf("%s", underline);
		// printf("end \n");

}

// produces a set of spaces before the underline
void underline_correct_spelling(char *tkn, char* underline)
{
	int j = strlen(tkn);
    int i = 0;
	for(; i < j; i++) {
    		strcat(underline, " ");
	}
		strcat(underline, " ");

}

//given a list of bad words in order, underline them in sentence
char* underline_misspelled_sentence(char** badwords, char* sentence, int element) {

	char* underline = malloc(strlen(sentence));
	underline[0] = '\0'; 

	while(badwords[element] != NULL) {

		char *ptr = strstr(sentence, badwords[element]);

		if(ptr != NULL) {

			int pos = ptr - sentence;

			int i = 0;
			size_t j = 0;

			for(; i < pos; i++) {

				strcat(underline, " ");

			}

			for (; j < strlen(badwords[element]); j++) {

				strcat(underline, "^");

			}

			sentence = ptr+strlen(badwords[element]);

		}

		element++;

	}

	return underline;

}



// add word in line to list of bad words (i.e. misspelled words not in the file)
int add_to_badwords(char *badword, char** badwords)
{
	if (badword == NULL || badwords == NULL) {
		return EXIT_FAILURE;
	}
	int i = 0;
	while(badwords[i] != NULL) {
		i++;
	}
	badwords[i] = badword;
	return EXIT_SUCCESS;
	// printf("adding badword %s", badword);
	// printf("i is %d ", i);
}

//takes in a line, identifies incorrect words, and generates a string of underlines  
int parse_string(char* string, dict_t *dict, char *underline, char** badwords)
{
	char *tkn = strtok(string, ": ,.-'\n'" ""); //words only separated by these punctuation
	while (tkn != NULL) {

		if (valid_word(tkn, dict) == EXIT_FAILURE){
			//printf("%s ", tkn);
			underline_misspelled(tkn, underline);
			add_to_badwords(tkn, badwords);
		}
		else if (valid_word(tkn, dict) == EXIT_SUCCESS) {
			//printf("%s ", tkn);
			underline_correct_spelling(tkn, underline);
		}
		else {
			printf("error processing text");
			return EXIT_FAILURE;
		}
		tkn = strtok(NULL, " ,.-");
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



//initialises each element in array (that stores misspelled words in a line) to NULL
int initialize_badwords(char **badwords, int length)
{

	if (badwords==NULL) {
		return EXIT_FAILURE;
	}
    int i = 0;
	for ( ; i < length; i++) {
    	badwords[i] = NULL; //initialize each element to be NULL
    }

    return EXIT_SUCCESS;
}



/*
 *	III. Interactive Mode
 */

/* Functions needed for interactive mode */
char* edit_interactive(char* line, dict_t* dict, int linenumber)
{
    char *line_copy = malloc(strlen(line));
    strcpy(line_copy, line); //maintain a copy of the line to preserve original line: line will be parsed into individual words
    
    char *line_copy2 = malloc(strlen(line));
    strcpy(line_copy2, line); 
    int max_no_suggestions = 2; //should the user decide this?


    int length = strlen(line) / 3; //approximate 3 chars per word to be safe
    char *badwords[length]; //generates an empty array where the misspelled words in a line will be stored
    initialize_badwords(badwords, length);

    char *underline = (char *)malloc(strlen(line + 1)); //generate an empty array where the underline will go
    underline[0] = '\0'; 
    //char underline[strlen(line)] = "";


    parse_string(line, dict, underline, badwords); //identify misspelled words and add to bad_word, 
    //add to underline function 
    
    printf("Current line number is %d: \n", linenumber);
    printf("%s", line_copy);
    printf("\n");
    printf("%s", underline);
    printf("\n\n");

    // printf("Misspelled words in this sentence are: ");

    // int i = 0;
    // while(badwords[i] != NULL) {
    // 	printf("%d: %s ",i+1, badwords[i]);
    // 	i++;
    // }
    // printf("\n");
    // int number1;
    // printf("Enter the number value of the word you would like to change: ");
    // scanf("%d", &number1);

    char *suggestions[max_no_suggestions]; //generates empty array where suggestions will be filled
 
    int i = 0;

    //replacing words according to user suggestions
      while (badwords[i] != NULL) {
    	int success = generate_suggestions(badwords[i], dict, suggestions);

    	if(success != -1) {
    	printf("Possible replacements for word %s are: ", badwords[i]);
    	printf("0: Delete Word. ");
    	printf("1: No replacement. ");
        int j = 0;
    	for ( ; j < max_no_suggestions; j++) {
    		printf("%d : %s ", j+2, suggestions[j]);

    	}  	

       }
       printf("\n\n");

    
    //gets replacement choice from user
    int number2;
    printf("Enter the number of the replacement: ");

    int check = scanf("%d", &number2);
    assert(check >= 0);

    if (number2 == 0) {
    	printf("Deleting %s.", badwords[i]);
    	correct_line(line_copy, badwords[i], "");
    	printf("New sentence is: \n\n");
     	printf("%s\n\n", line_copy);
     	//printf("%s\n", badwords[i+1]);
     	printf("%s\n", underline_misspelled_sentence(badwords, line_copy, i+1));


    }

    else if (number2 == 1) {
    	printf("No changes made to %s. \n\n", badwords[i]);

    }

    else if (number2 > (max_no_suggestions+2)) {
    	shell_error("Please enter a valid number");
    }

    else if (number2 != 1 || number2 != 0) { //1 if no replacement needed, 0 if word deleted
    	printf("Replacing %s with %s \n", badwords[i], suggestions[number2-2]);
    	correct_line(line_copy, badwords[i], suggestions[number2-2]); //modifies line function
    	printf("New sentence is: \n");
     	printf("%s\n\n", line_copy);
     	printf("%s\n", underline_misspelled_sentence(badwords, line_copy, i+1));
    }


	i++;	// added loop changer
  }

	return line_copy;
	// need a way for string to (a) preserve punctuations and (b) 
	// @Sarika this would be where the program needs replace_word, ignore_word, alternate_spelling
}


/* interctive mode - open file, parse and work on later */
char** interactive_mode(char* filename, dict_t* dict, int* quit) //will pass in dictionary later
{

	size_t max_terminal_line_length = 500; //what is a reasonable estimate?

	char** lines;

	lines = parse_file(filename);


	

	// step through phases
	int i=0;
	while (lines[i] != NULL) {	// potential error - one empty line in the middle of two full?	
		int linenumber = i+1;
		if (strlen(lines[i]) <= max_terminal_line_length) {
			lines[i] = edit_interactive(lines[i], dict, linenumber);
		}//edit interactive is called for each line 
		else {
			//deniz code here?

		}
		i++;
	}

    *quit = 0;
	return lines;
}

/* 
	IV. Batch Mode
 */
// Adapted from sarika's edit_interactive
char* edit_batch(char* line, dict_t* dict, int verbosity)
{
    char *line_copy = malloc(strlen(line));
    strcpy(line_copy, line); //maintain a copy of the line to preserve original line: line will be parsed into individual words
    int max_no_suggestions = 1; //need only one suggestion

    int length = strlen(line)/3; //approximate 3 chars per word to be safe
    char *badwords[length]; //generates an empty array where the misspelled words in a line will be stored
    initialize_badwords(badwords, length);

    char *underline = (char *)malloc(strlen(line + 1)); //generate an empty array where the underline will go
    underline[0] = '\0'; 
    parse_string(line, dict, underline, badwords); //identify misspelled words and add to bad_word, 

    char *suggestions[max_no_suggestions]; //generates empty array where suggestions will be filled


    int i = 0;
    //replacing words, printing out if batch mode
    while (badwords[i] != NULL) {
        int success = generate_suggestions(badwords[i], dict, suggestions);
	    if (success == -1) suggestions[0] = badwords[i];
    	    correct_line(line_copy, badwords[i], suggestions[0]);
	    if (verbosity) printf("WORD:%s\nREPLACEMENT:%s\n\n", badwords[i], suggestions[0]);    // print list of replacement
	    i++;
	}

	return line_copy;
}

char** batch_mode(char* filename, dict_t* dict, int* quit, int verbosity)
{
	if (verbosity) printf("\nBatch Mode: Verbose\n\n");

	char** lines;
	lines = parse_file(filename);
	// if lineparse_file returns NULL
	if (lines == NULL) {
		shell_error("file parsing error: check txt file");
		*quit=1;
	}

	int i=0;
	while (lines[i] != NULL) {
		if (verbosity) printf("Line number: %d\n",i+1);
		lines[i] = edit_batch(lines[i], dict, verbosity);
		i++;
	}

	return lines;
}

/*
	V. Main Page
 */


/* Prints help page. Returns to main page via loop in main function */
void help_page()
{
    shell_help();
	shell_prompt();

	parse_read_line();      // accept any input in the command line
}

/* Check if file with name, given by string, exists */
int fileexists(const char* filename)
{
	struct stat buffer;
	return (stat(filename, &buffer) == 0);
}

/* helper for main_page, determine input mode */

int change_mode(char* arg)
{
	int a = atoi(arg);
    if ((a == 1) | (a == 2) | (a == 3)) {
        return a;
	} else {
        shell_error("Argument unrecognizeable: return to default interactive mode");		
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
		args = parse_split_line(line);

		if (args == NULL || args [2] != NULL) { // 3 inputs, or no input
			shell_error("Please type in one of the indicated commands!");
			*quit = 0;
		} else if (!strcmp(args[0],"h")) { // Print help page and exit
			help_page();
			*quit = 0;
		} else if (!strcmp(args[0],"f")) { // Check valid file path, then exit. If not, redo loop
			if(!fileexists(args[1])) {
				shell_error("\n\nPlease enter a valid file path for a new edit target!");
				*quit = 0;
			} else {
			strcpy(file_name,args[1]);
			printf("\n\nInput file is now %s\n\n\n",file_name);
			*quit=1;
			}
		} else if (!strcmp(args[0],"d")) { // Check file path validity for dicitonary
			if(!fileexists(args[1])) {
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
			*mode = change_mode(args[1]);
			printf("Mode changed to %d\n",atoi(args[1]));
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
