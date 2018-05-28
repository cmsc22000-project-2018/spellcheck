
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
    printf("------- Welcome to Spellcheck! ------\n\n");

    printf("Please load a file to begin. Additionally, select an output mode and/or choose dictionary before running the program.\n\n");

    printf("f [/path/file.txt]           : open file\n");
    printf("d [/path/dictionary.txt]     : input custom dictionary file\n");
    printf("m [number]                   : switch output mode - quiet (1) verbose (2) or interactive (3) \n");
    printf("h                            : help\n");
    printf("q                            : quit program\n");
}

/* See shellstrings.h */
void shell_save() {
    printf("p : print all changes\n");
    printf("s : save to existing file\n");
    printf("c : save to custom file\n");
    printf("q : quit program\n\n");
}

/* See shellstrings.h */
void shell_print(char** lines) {
    int i = 0;

    printf("\n\n");
    while (lines[i] != NULL) {
        printf("%s", lines[i]);
        i++;
    }
    printf("\n\n");
}


/* See shellstrings.h */
void shell_error(char* error_text) {
	printf("=> ERROR: %s <=\n", error_text);
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
    printf("\nspellcheck > ");
}

/* See shellstrings.h */
void shell_input(char* input_file, char* status) {
    char *i = "has been accepted as the input file for";
    printf("%s %s %s!\n", input_file, i, status);
}

/* See shellstrings.h */
void shell_help() {
    printf("Spellcheck is a tool which searches for misspelled words and suggests alternative spellings given a text file.\n");
    printf("For interactive mode, run: r [/path/file.txt]\n");
    printf("For batch mode, exit the program, and run: $ ./spellcheck [/path/file.txt] [-flag]\n");
    printf("Flags:  -q is for quiet, -v is for verbose, and -s is for saving a file to a custom destination.\n");
    printf("Enter any command to return to the previous page.\n");
}

/* See shellstrings.h */
void shell_outro() {
    printf("Thank you for using Spellcheck. Bye!\n");
}

/* See shellstrings.h */
void shell_verbose_chart(int lnum, char* misspelled, char** suggestions) {
    printf("%d\t\t\t", lnum); // print line number
    int ntab = 3 - (strlen(misspelled) / 8); // number of tabs
    int j;
    printf("%s", misspelled);
    for (j = 0; j < ntab; j++) printf("\t");

    j = 0;
    while (suggestions[j] != NULL) {
        printf("%s", suggestions[j]);
        if (suggestions[j + 1] != NULL) printf(", ");
        j++;

    }
    printf("\n"); // print list of replacement
}


