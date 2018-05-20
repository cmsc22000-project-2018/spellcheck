
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

    printf("s               : save to existing file\n");
    printf("c               : save to custom file\n");
    printf("r               : return to home screen\n");
    printf("q               : quit program\n\n");
}

void shell_parse_success() {
    printf(GREEN "File editing successful!\n\n" RESET);
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

void shell_interactive_start(char* file_name, char* dict_name, char* md) {
    printf("\n\n" BOLDWHITE "------------------------------------------------------------\n" RESET);
    printf(BOLDWHITE "--------------------EDITING STARTED WITH--------------------\n" RESET);
    printf("\n" BOLDWHITE "------------------------------------------------------------\n" RESET);
    printf("file: %s\ndictionary: %s\nmode: %s\n\n", file_name, dict_name, md);
    printf("Enter any command to start interactive\n\n");
}

void shell_batch_start(char* file_name, char* dict_name, char* md) {
    printf(BOLDWHITE "--------------------EDITING STARTED WITH--------------------\n" RESET);
    printf("file: %s dictionary: %s\n mode: %s\n\n", file_name, dict_name, md);
}

void shell_dict_message(int i) {
    if (i == EXIT_SUCCESS) {
        printf("Dictionary successfully parsed!\n");
    } else {
        printf("Trouble reading dictionary, exiting program\n");
        exit(0);
    }
}

char* shell_modename(int mode) {
    switch (mode) {
        case 1: return "quiet batch mode";
        case 2: return "verbose batch mode";
        case 3: return "interactive mode";
        default: break;
    }
    return "interactive mode";
}

void shell_save_message() {
    printf("\n\n Enter a viable file name [path/*.txt] or enter 'r' to return to previous page.\n\n");
    shell_prompt();
}

void shell_interactive_line_print(int lnum, char* line, char* underline) {
    printf("Current line number is %d: \n", lnum);
    printf("%s\n", line);
    printf("%s\n\n", underline);
}

void shell_interactive_replacements(char* word, char** sug, int nsug) {
    printf("Possible replacements for word \"%s\" are: \n\n", word);
    printf("0: Delete Word.\n");
    printf("1: No replacement.\n");
    int j = 0;
    for ( ; j < nsug; j++) {
        printf("%d: %s\n", j+2, sug[j]);
    }
    printf("\n\n");
    shell_prompt();
}

void shell_verbose_start() {
    printf("\nBatch mode: Verbose\n\n");
}

void shell_line_number(int lnum) {
    printf("Line number: %d\n", lnum+1);
}

void shell_verbose_replacement(char* word, char* sug) {
    printf("Word:%s\nReplacement: %s\n\n", word, sug);
    shell_prompt();
}

