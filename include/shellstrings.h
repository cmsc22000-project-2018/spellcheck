
/* 
 * String output functions to be used in the shell
*/

#ifndef _SHELLSTRINGS_H
#define _SHELLSTRINGS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Colors to be used in strings for the shell strings */
#define RESET       "\033[0m"               // Reset color
#define RED         "\033[31m"              // Red 
#define GREEN       "\033[32m"              // Green
#define YELLOW      "\033[33m"              // Yellow
#define BLUE        "\033[34m"              // Blue
#define WHITE       "\033[37m"              // White
#define BOLDRED     "\033[1m\033[31m"       // Bold Red
#define BOLDGREEN   "\033[1m\033[32m"       // Bold Green
#define BOLDYELLOW  "\033[1m\033[33m"       // Bold Yellow
#define BOLDBLUE    "\033[1m\033[34m"       // Bold Blue
#define BOLDWHITE   "\033[1m\033[37m"       // Bold White

/* Home Page */
void shell_greeting();

/* Save Page */
void shell_save();

/* Print error, allowing for description depending on context */
void shell_error(char* s);

/* Command Line Input Format */
void shell_usage();

/* Shell Prompt */
void shell_prompt();

/* File input in Terminal */
void shell_input(char* input_file, char* status);

/* Help Page */
void shell_help();

/* Final message */
void shell_outro();

#endif
