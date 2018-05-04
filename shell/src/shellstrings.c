/* Shell Functions
   Jaewan Park
*/

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

void save_help_text()
{
}

void greet()
{
	char g[] = "------- Welcome to Spellcheck! ------\n";
	printf("%s",g);
}

void error_shell(char* s)
{
	fprintf(stderr,"=> ERROR: %s <=\n",s);
}
