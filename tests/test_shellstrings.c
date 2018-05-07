#include <stdio.h>
#include <criterion/criterion.h>
#include "shell.h"


Test(shell,mainpage)
{
	char p[] =
	"------- Welcome to Spellcheck! ------\n"
        "Please load a file into spellcheck to begin. Additionally, select mode and choose dictionary.\n\n"
        "h                            : help\n"
        "r [~/path/file.txt]          : read a file into spellcheck\n"
        "d [~/path/dictionary.txt]    : read dictionary file into spellcheck\n"
        "q                            : quit program\n\n";

	// compare to string
}
