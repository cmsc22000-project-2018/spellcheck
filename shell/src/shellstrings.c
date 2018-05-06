/* Strings to be used in shell
   Jaewan Park
*/
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include "shellstrings.h"

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

void greet()
{
	char g[] = "------- Welcome to Spellcheck! ------\n\n";
	printf("%s",g);
}

void error_shell(char* s)
{
	printf("=> ERROR: %s <=\n",s);
}

void shell_prompt()
{
	char p[] = "spellcheck > ";
	printf("%s",p);
}

void bye()
{
	char b[] = "Thank you for using Spellcheck. Bye!\n";
	printf("%s",b);
}

void usage()
{
	char u[] =
	"Please use designated format:\n\n"
	"./spellcheck or \n"
	"./spellcheck [~/path/file.txt] [-flag] [~/path/destination.txt] \n";
	printf("%s",u);
}
