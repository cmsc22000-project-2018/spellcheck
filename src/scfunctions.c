#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "scfunctions.h"
#include "dictionary.h"
#include "word.h"

/* 
	Order of functions:
		I. Saving files
		II. Functions for editing strings (lines)
		III. Interactive Mode
		IV. Batch Mode
		V. Main Page
 */


/*
	I. Saving Files
 */

void save_corrections(char* filename, char** lines)
{
	FILE* f=fopen(filename,"w");
	int i=0;
	while (lines[i] != NULL) {
		fprintf(f,"%s",lines[i]);
		i++;
	}
	fclose(f);
}

void save_page(char* filename, char** lines,int* quit)
{
	int i=1;

	while (i) {
		save_page_text();
		shell_prompt();
		i=0;
		char* line;
		char** args;

		line=read_line();
		args=split_line(line);


		if (args == NULL || args [1] != NULL) { // More than 1 input, or no input
			error_shell("\nPlease type in one of the indicated commands!\n\n");
			i=1;
		} else if (!strcmp(args[0],"w")) {
			save_corrections(filename,lines);
			*quit=0;
		} else if (!strcmp(args[0],"s")) {
			save_corrections(args[1],lines);
			*quit=0;
		} else if (!strcmp(args[0],"r")) {
			*quit=1;
		} else if (!strcmp(args[0],"q")) {
			*quit=0;
		} else {
			error_shell("\nPlease type in one of the indicated commands!\n\n");
			i=1;
		}
	}
}

/*
	II. Functions for editing strings
*/

void underline_misspelled(char *tkn, char* underline) {
	for(int i = 0; i < strlen(tkn); i++) {
    	strcat(underline, "^");
	}
		strcat(underline, " ");
		// printf("start \n");
		// printf("%s", underline);
		// printf("end \n");

}

void underline_correct_spelling(char *tkn, char* underline) {
		for(int i = 0; i < strlen(tkn); i++) {
    		strcat(underline, " ");
	}
		strcat(underline, " ");

}



void add_to_badwords(char *badword, char** badwords) {
	int i = 0;
	while(badwords[i] != NULL) {
		i++;
	}
	badwords[i] = badword;
	// printf("adding badword %s", badword);
	// printf("i is %d ", i);
}

//takes in a line, identifies incorrect words, and generates a string of underlines  
void parse_string(char* string, dict_t *dict, char *underline, char** badwords) {

	
	char *tkn = strtok(string," ,.-'\n'"); //words only separated by these punctuation
	while (tkn != NULL) {

		if (valid_word(tkn, dict) == 0){
			//printf("%s ", tkn);
			underline_misspelled(tkn, underline);
			add_to_badwords(tkn, badwords);
		}
		else if (valid_word(tkn, dict) == 1) {
			//printf("%s ", tkn);
			underline_correct_spelling(tkn, underline);
		}
		else {
			printf("error processing text");
		}
		tkn = strtok(NULL," ,.-");
	}

}

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
char* correct_line(char* line, char* old_word, char* new_word) {
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
}



//initialises each element in array (that stores misspelled words in a line) to NULL
void initialize_badwords(char *badwords, int length) {

	    for (int i = 0; i < length; i++) {
    	badwords[i] = NULL; //initialize each element to be NULL
    }


}



/* Functions needed for interactive mode */
char* edit_interactive(char* line, dict_t* dict)
{

    char *line_copy = malloc(strlen(line));
    strcpy(line_copy, line); //maintain a copy of the line to preserve original line: line will be parsed into individual words
    int max_no_suggestions = 2; //should the user decide this?


    int length = strlen(line)/3; //approximate 3 chars per word to be safe
    char *badwords[length]; //generates an empty array where the misspelled words in a line will be stored
    initialize_badwords(badwords, length);

    char *underline = (char *)malloc(strlen(line + 1)); //generate an empty array where the underline will go
    underline[0] = '\0'; 
    //char underline[strlen(line)] = "";


    parse_string(line, dict, underline, badwords); //identify misspelled words and add to bad_word, 
    //add to underline function 
    
	printf("%s", line_copy);
    printf("\n");
    printf("%s", underline);
    printf("\n");



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
    	printf("1: No replacement ");
    	for (int j = 0; j < max_no_suggestions; j++) {
    		printf("%d : %s ", j+2, suggestions[j]);

    	}  	

       }

    
    //gets replacement choice from user
    int number2;
    printf("Enter the number of the replacement: ");
    scanf("%d", &number2);

    if (number2 != 1) { //1 if no replacement needed
    	printf("Replacing %s with %s \n", badwords[i], suggestions[number2-2]);
    	correct_line(line_copy, badwords[i], suggestions[number2-2]); //modifies line function
    	printf("Corrected sentence is: \n");
     	printf("%s \n", line_copy);
    }



	return line_copy;
	// need a way for string to (a) preserve punctuations and (b) 
	// @Sarika this would be where the program needs replace_word, ignore_word, alternate_spelling

}



/* interctive mode - open file, parse and work on later */

void interactive_mode(char* filename, int* quit) //will pass in dictionary later
{
	char** lines;

	lines = lineparse_file(filename);

	dict_t* dict;

	dict = dict_new();
	if (read_to_dict("tests/sample_dict.txt", dict) == 1) {
		printf("Dictionary successfully read! \n");
	}
	else {
		printf("Trouble reading dictionary \n");
	}

	// step through phases
	int i=0;
	while (lines[i] != NULL) {	// potential error - one empty line in the middle of two full?	
		lines[i] = edit_interactive(lines[i], dict); //edit interactive is called for each line 
		i++;
	}

	// call save
	save_page(filename, lines, quit);

	// free lines
	i=0;
	while(lines[i]!=NULL) {
		free(lines[i]);
		i++;
	}
	free(lines);
}

/* 
	IV. Batch Mode
 */

char* edit_batch(char* line, dict_t* dict, int verbosity)
{
	// generate bad words

	// generate replacements

	// replace string

	return line;
}

void batch_mode(char* filename, dict_t* dict, int* quit, int verbosity)
{
	char** lines;
	lines = lineparse_file(filename);
	// if lineparse_file returns NULL
	if (lines == NULL) {
		shell_error("file parsing error: check %s\n",filename);
		*quit=1;
	}

	int i=0;
	while (lines[i] != NULL) {
//		lines[i] = edit_batch(lines[i], dict, verbosity);
		i++;
	}

	// call save
	save_page(filename, lines, quit);

	i=0;
	while(lines[i]!=NULL) {
		free(lines[i]);
		i++;
	}
	free(lines);
}

/*
	V. Main Page
 */


/* Prints help page. Returns to main page via loop in main function */
void help_page()
{
	help_page_text();
	shell_prompt();

	read_line();
}

/* Check if file with name, given by string, exists */
int fileexists(const char* filename)
{
	FILE *file;
	if (file=fopen(filename,"r")) {
		fclose(file);
		return EXIT_SUCCESS;
	}

	return EXIT_FAILURE;
}

/* helper for main_page, determine input mode */
int mode(char* arg)
{
	switch (arg) {
		case '1'; return atoi(arg);	// might be "
		case '2'; return atoi(arg);
		case '3'; return atoi(arg);
		default: // error case
			shell_error("\n");
			
	}
}

void main_page(int* quit, int *mode, char* file_name, char* dict_name)
{
	while (!(*quit)) {

	main_help_text();
	shell_prompt();

	char* line;
	char** args;

	line = read_line();
	args = split_line(line);

	if (args == NULL || args [2] != NULL) { // 3 inputs, or no input
		error_shell("Please type in one of the indicated commands!\n\n");
		*quit=0;
	} else if (!strcmp(args[0],"h")) { // Print help page and exit
		help_page();
		*quit=0;
	} else if (!strcmp(args[0],"r")) { // Check valid file path, then exit. If not, redo loop
		if(!fileexists(args[1])) {
			error_shell("Please enter a valid file path for a new edit target!\n\n");
			*quit=0;
		} else {
		file_name = args[1];
		*quit=1;
		}
	} else if (!strcmp(args[0],"d")) { // Check file path validity for dicitonary, then redo loop
		if(!fileexists(args[1])) {
			error_shell("Please enter a valid file path for a new dictionary!\n\n");
			*quit=0;
		} else {
		dict_name = args[1];
		*quit=0;
		}
	} else if (!strcmp(args[0],"q")) { // quit
		*quit=2;
	} else if (!strcmp(args[0], "m")) { // change mode
		*mode = mode_change(args[1]);
		if(!fileexists(file_name)){
			*quit=0;
		} else {
			*quit=1;
		}
	} else { // input bad
		error_shell("Please type in one of the indicated commands!\n\n");
		*quit=0;
	}

	free(line);
	free(args);

	}
}
