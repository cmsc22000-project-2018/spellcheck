/* Strings to be used in shell
   Jaewan Park
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "shellstrings.h"

/* Home Page */
void greet()
{
	char g[] = "------- Welcome to Spellcheck! ------\n\n";
	printf("%s",g);
}

void main_help_text()
{
	char m[] =
	"Please load a file into spellcheck to begin. Additionally, select mode and choose dictionary.\n\n"
	"h                            : help\n"
	"r [~/path/file.txt]          : read a file into spellcheck\n"
	"d [~/path/dictionary.txt]    : read dictionary file into spellcheck\n"
	"q                            : quit program\n\n";
	printf("%s",m);
}

/* Help Page */
void help_page_text()
{
	char h[] =
	"\n\n Spellcheck is a tool which, given a text file, will search for misspelled words and will suggest alternative spellings.\n\n\n"
	"To run interactive mode on a file, return to the previous page and run:\n\n"
	"\t r [~/path/file.txt]\n\n"
	"To run batch mode, exit program, and run:\n\n"
	"\t $ ./spellcheck [~/path/file.txt] [-flag]\n\n"
	"-q is for quiet, -v is for verbose, and -s saves a file to another destination.\n\n"
	"Press any key to return to the previous page.\n\n\n";
	printf("%s",h);
}

/* Save Page */
void save_page_text()
{
	char s[] =
	"File editing successful!\n"
	"w                     : save file with corrections\n"
	"s [~path/name.txt]    : save corrections to new file\n"
	"r                     : return to program's home screen\n"
	"q                     : quit program\n";
	printf("%s",s);
}

/* Print error, allowing for description depending on context */
void error_shell(char* s)
{
	printf("=> ERROR: %s <=\n",s);
}

/* Command Line Input Format */
void usage()
{
	char u[] =
	"Please use designated format:\n\n"
	"./spellcheck [-flag] [~/path/file.txt] [-saveflag] [~/path/destination.txt] \n\n"
	"For help, run without command line arguments and enter help page\n";
	printf("%s",u);
}

/* Shell Prompt */
void shell_prompt()
{
	char p[] = "spellcheck > ";
	printf("%s",p);
}

/* Final message */
void bye()
{
	char b[] = "Thank you for using Spellcheck. Bye!\n";
	printf("%s",b);
}

/* File input */
void input(char* input_file, char* status)
{
	char i[] = "has been accepted as the input file for";
	printf("%s %s %s!\n",input_file,i,status);
}
