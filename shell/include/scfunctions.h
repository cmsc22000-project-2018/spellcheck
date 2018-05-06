#ifndef _SCFUNCTIONS_H
#define _SCFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"

/* functions for saving files */
void save_corrections(char* filename, char** lines);

void save_page(char* filename, char** lines,int* quit);

/* Functions needed for batch mode */
void batch_mode(int argc, char **argv);

/* Functions needed for interactive mode */
char* edit_interactive(char* line);

void interactive_mode(char** filename, int* quit);

/* Prints help page. Returns to main page via loop in main function */
void help_page();

/* function for main page */
int main_page(int* quit);



#endif
