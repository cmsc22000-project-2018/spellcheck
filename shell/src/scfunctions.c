#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "shellstrings.h"
#include "parser.h"
#include "scfunctions.h"
#include "dictionary.h"
#include "word.h"




void save_corrections(char* filename, char** lines)
{
	FILE* f=fopen(filename,"w");
	int i=0;
	while (lines[i] != NULL) {
		fprintf(f,"%s",lines[i]);
		i++;
	}
	fclose(f);
}

void save_page(char* filename, char** lines,int* quit)
{
	int i=1;

	while (i) {
		save_page_text();
		shell_prompt();
		i=0;
		char* line;
		char** args;

		line=read_line();
		args=split_line(line);

		assert(args!=NULL);

		if (!strcmp(args[0],"w")) {
			save_corrections(filename,lines);
			*quit=0;
		} else if (!strcmp(args[0],"s")) {
			save_corrections(args[1],lines);
			*quit=0;
		} else if (!strcmp(args[0],"r")) {
			*quit=1;
		} else if (!strcmp(args[0],"q")) {
			*quit=0;
		} else {
			error_shell("please type in one of the indicated commands!");
			i=1;
		}
	}
}


void underline_misspelled(char *tkn, char* underline) {
	for(int i = 0; i < strlen(tkn); i++) {
    	strcat(underline, "^");
	}
		strcat(underline, " ");
		// printf("start \n");
		// printf("%s", underline);
		// printf("end \n");

}

void underline_correct_spelling(char *tkn, char* underline) {
		for(int i = 0; i < strlen(tkn); i++) {
    		strcat(underline, " ");
	}
		strcat(underline, " ");

}



void add_to_badwords(char *badword, char** badwords) {
	int i = 0;
	while(badwords[i] != NULL) {
		i++;
	}
	badwords[i] = badword;
	// printf("adding badword %s", badword);
	// printf("i is %d ", i);
}

/* Functions needed for batch mode */
//void batch_mode(int argc, char **argv)
//{
//	// implmenent after having interactive success
//}


//taking a line and dividing into words
void parse_string(char* string, dict_t *dict, char *underline, char** badwords) {

	
	char *tkn = strtok(string," ,.-'\n'"); //words only separated by these punctuation
	while (tkn != NULL) {

		if (valid_word(tkn, dict) == 0){
			printf("%s ", tkn);
			underline_misspelled(tkn, underline);
			add_to_badwords(tkn, badwords);
		}
		else if (valid_word(tkn, dict) == 1) {
			printf("%s ", tkn);
			underline_correct_spelling(tkn, underline);
		}
		else {
			printf("error processing text");
		}
		tkn = strtok(NULL," ,.-");
	}

}

//reference from https://stackoverflow.com/questions/32413667/replace-all-occurrences-of-a-substring-in-a-string-in-c
char* correct_line(char* line, char* old_word, char* new_word) {
	char buffer[2000] = {0}; //again, we might need to modify our size estimates
	char *insert_point = &buffer[0];
	char *tmp = line;
	int old_length = strlen(old_word);
	int new_length = strlen(new_word);

	while(1) {
		char *p = strstr(tmp, old_word);

		if (p == NULL) {
			strcpy(insert_point, tmp);
			break;
		}

		memcpy(insert_point, tmp, p - tmp);
		insert_point += p - tmp;

		memcpy(insert_point, new_word, new_length);
		insert_point += new_length;

		tmp = p + old_length;
	}

	strcpy(line, buffer);
}








/* Functions needed for interactive mode */
char* edit_interactive(char* line, dict_t* dict)
{

    char *line_copy = malloc(strlen(line));
    strcpy(line_copy, line);

    int length = strlen(line)/3; //approximate 3 chars per word to be safe
    int max_no_suggestions = 2; //should the user decide this?
    char *badwords[length]; 
    for (int i = 0; i < length; i++) {
    	badwords[i] = NULL;
    }
    char *underline = (char *)malloc(strlen(line + 1));
    underline[0] = '\0';
    //char underline[strlen(line)] = "";
    parse_string(line, dict, underline, badwords);
    printf("\n");
    printf("%s", underline);
    printf("\n");



    printf("Misspelled words in this sentence are: ");

    int i = 0;
    while(badwords[i] != NULL) {
    	printf("%d: %s ",i+1, badwords[i]);
    	i++;
    }
    printf("\n");
    int number1;
    printf("Enter the number value of the word you would like to change: ");
    scanf("%d", &number1);

    char *suggestions[max_no_suggestions]; 

    int success = generate_suggestions(badwords[number1-1], dict, suggestions);

    if(success != -1) {
    	printf("Possible replacements are: ");
    	printf("1: No replacement ");
    	for (int i = 0; i < max_no_suggestions; i++) {
    		printf("%d : %s ", i+2, suggestions[i]);

    	}  	

    }

    int number2;
    printf("Enter the number of the replacement: ");
    scanf("%d", &number2);

    if (number2 != 1) {
    	printf("Replacing %s with %s \n", badwords[number1-1], suggestions[number2-2]);
    	correct_line(line_copy, badwords[number1-1], suggestions[number2-2]);
    	printf("Correct sentence is: \n");
     	printf("%s \n", line_copy);
    }












	return line_copy;
	// need a way for string to (a) preserve punctuations and (b) 
	// @Sarika this would be where the program needs replace_word, ignore_word, alternate_spelling

}

void interactive_mode(char** filename, int* quit)
{
	char** lines;

	lines = lineparse_file(filename[1]);

	dict_t* dict;

	dict = dict_new();
	if (read_to_dict("sample_dict.txt", dict) == 1) {
		printf("Dictionary successfully read! \n");
	}
	else {
		printf("Trouble reading dictionary \n");
	}

	// step through phases
	int i=0;
	while (lines[i] != NULL) {	// potential error - one empty line in the middle of two full?	
		lines[i] = edit_interactive(lines[i], dict);
		i++;
	}

	// call save
	save_page(filename[1], lines, quit);

	// free lines
	i=0;
	while(lines[i]!=NULL) {
		free(lines[i]);
		i++;
	}
	free(lines);
}

/* Prints help page. Returns to main page via loop in main function */
void help_page()
{
	help_page_text();
	shell_prompt();

	read_line();
}

int main_page(int* quit)
{
	main_help_text();
	shell_prompt();

	char* line;
	char** args;

	line = read_line();
	args = split_line(line);

	if (!strcmp(args[0],"h")) {
		help_page();
		*quit=0;
	} else if (!strcmp(args[0],"r")) {
		if(args[1] == NULL) {
			error_shell("Please indicate a file!");
			*quit=0;
			return 0;
		}
		interactive_mode(args,quit);
		*quit=0;
	} else if (!strcmp(args[0],"d")) {
		// read_to_dict;
		*quit=0;
	} else if (!strcmp(args[0],"q")) {
		*quit=1;
	} else {
		error_shell("Please type in one of the indicated commands!");
		*quit=0;
	}

	free(line);
	free(args);

	return 1;
}
