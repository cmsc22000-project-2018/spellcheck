/* Strings to be used in shell
   Jaewan Park
*/
#include <stdlib.h>
#include <strings.h>
#include "shellstrings.h"

char* main_help_text()
{
	char m[] =
	"Please load a file into spellcheck to begin. Additionally, select mode and choose dictionary.\n\n"
	"h                            : help\n"
	"r [~/path/file.txt]          : read a file into spellcheck\n"
	"d [~/path/dictionary.txt]    : read dictionary file into spellcheck\n"
	"q                            : quit program\n\n";
	return m;
}

char* help_page_text()
{
	char h[] =
	"Spellcheck is a  tool which, given a text, will search for misspelled words and will suggest alternative spellings.\n\n\n"
	"To run interactive mode on a file, return to the previous page and run:\n\n"
	"\t r [~/path/file.txt]\n\n"
	"To run batch mode, exit program, and run:\n"
	"\t $ ./spellcheck [~/path/file.txt] [-flag]\n"
	"-q is for quiet, -v is for verbose, and -s saves a file to another destination."
	"Press any key to return to the previous page.\n\n"
	return h;
}

char* save_page_text()
{
	char s[] =
	"File editing successful!\n"
	"w                     : save file with corrections\n"
	"s [~path/name.txt]    : save corrections to new file\n"
	"r                     : return to program's home screen\n"
	"q                     : quit program\n";
	return s;
}

char* greet()
{
	char g[] = "------- Welcome to Spellcheck! ------\n";
	return g;
}

char* error_shell(char* s)
{
	fprintf(stderr,"=> ERROR: %s <=\n",s);
}

char* shell_prompt()
{
	char p[] = "spellcheck > ";
	return p;
}
