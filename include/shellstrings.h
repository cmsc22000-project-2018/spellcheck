/* Shell interface functions
   Jaewan Park
*/

#ifndef _SHELLSTRINGS_H
#define _SHELLSTRINGS_H
#include <stdio.h>
#include <strings.h>

void main_help_text();

void help_page_text();

void save_page_text();

void greet();

void error_shell(char* s);

void bye();

void usage();

void shell_prompt();

void interactive_correction(int lnum, char* sent, char* hglt, char** sugns, int snum);

void interactive_1();
void interactive_2();
void interactive_3();

#endif
