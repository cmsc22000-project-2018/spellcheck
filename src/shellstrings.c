
/* 
 * String output functions to be used in the shell
 *
 * See shellstrings.h for function documentation.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shellstrings.h"

/* See shellstrings.h */
void shell_intro() {
    printf(BOLDWHITE "------- Welcome to Spellcheck! ------\n\n" RESET);

    printf(BLUE "Please load a file to begin. Additionally, select an output mode and/or choose dictionary before running the program.\n\n" RESET);

    printf("f [/path/file.txt]           : open file\n");
    printf("d [/path/dictionary.txt]     : input custom dictionary file\n");
    printf("m [number]                   : switch output mode - quiet (1) verbose (2) or interactive (3) \n");
    printf("h                            : help\n");
    printf("q                            : quit program\n");
}

/* See shellstrings.h */
void shell_save() {
    printf(GREEN "File editing successful!\n\n" RESET);

    printf("p               : print result of edit\n");
    printf("s               : save to existing file\n");
    printf("c               : save to custom file\n");
    printf("r               : return to home screen\n");
    printf("q               : quit program\n\n");
}

void shell_print(char** lines) {
    int i = 0;

    printf(BOLDWHITE "\n Edited text: \n\n");

    while (lines[i] != NULL) {
        printf("Line %d: %s\n", i+1, lines[i]);
        i++;
    }
}

/* See shellstrings.h */
void shell_error(char* s) {
	printf(RED "=> ERROR: %s <=\n" RESET, s);
}

/* See shellstrings.h */
void shell_usage() {
    char *u =
    "Please use designated format:\n\n"
    "./spellcheck [-flag] [~/path/file.txt] [-saveflag] [~/path/destination.txt] \n\n"
    "For help, run without command line arguments and enter help page\n";
    printf("%s", u);
}

/* See shellstrings.h */
void shell_prompt() {
    printf(BOLDWHITE "\nspellcheck >" RESET " ");
}

/* See shellstrings.h */
void shell_input(char* input_file, char* status) {
    char *i = "has been accepted as the input file for";
    printf("%s %s %s!\n", input_file, i, status);
}

/* See shellstrings.h */
void shell_help() {
    printf(BLUE "Spellcheck is a tool which searches for misspelled words and suggests alternative spellings given a text file.\n" RESET);
    printf("For interactive mode, run:" BOLDWHITE "r [/path/file.txt]\n" RESET);
    printf("For batch mode, exit the program, and run:" BOLDWHITE "$ ./spellcheck [/path/file.txt] [-flag]\n" RESET);
    printf("Flags: " BOLDWHITE "-q" RESET " is for quiet, " BOLDWHITE "-v" RESET "is for verbose, and " BOLDWHITE "-s" RESET " is for saving a file to a custom destination.\n");
    printf(BLUE "Enter any command to return to the previous page.\n" RESET);
}

/* See shellstrings.h */
void shell_outro() {
    printf("Thank you for using Spellcheck. Bye!\n");
}



