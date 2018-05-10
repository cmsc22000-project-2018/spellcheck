#include <stdio.h>
#include "parser.h"
#include "shellstrings.h"
#include "scfunctions.h"

/*
Sample input:

    > ./spellcheck -i misspelled.txt

    Spellchecks misspelled.txt in interactive mode with the default dictionary


    > ./spellcheck -d my_dict.txt misspelled.txt

    Spellchecks in batch mode using custom dictionary my_dict.txt

*/

int main(int argc, char **argv) {

    // Support filenames up to 100 characters long
    char *dictionary_name = (char*)malloc(sizeof(char*) * 101);
    char *file_name = (char*)malloc(sizeof(char*) * 101);

    // Interactive mode flag- default 0 for batch
    int interactive = 0;

    // Just a default dictionary, can be updated with commandline args
    dictionary_name = "default_dict.txt";

    // Read the arguments from commandline
    for (int i = 0; i < argc; i++) {

        // Found a commandline flag
        if (argv[i][0] == '-') {

            if (argv[i][1] == 'd') {
                // Checks for a custom dictionary
                sscanf(argv[i+1], "%s", dictionary_name);
            } else if (argv[i][1] == 'i') {
                // If the interactive mode flag is used
                interactive = 1;
            } 

            // have more flags here
        }

        // Have special nonflag things here maybe?
    }

    // Asssume the last argument is the file to spellcheck
    sscanf(argv[argc - 1], "%s", file_name);

    // Then just handle stuff here with reading to dictionary and interavctive vs batch
}
