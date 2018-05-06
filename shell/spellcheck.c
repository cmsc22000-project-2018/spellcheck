#ifndef _SPELLCHECK_H
#define _SPELLCHECK_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "shellstrings.h"


/* This file will run the shell "spellcheck" for interacting with the dictionary and the file */
/* Adapted from  https://brennan.io/2015/01/16/write-a-shell-in-c/ */

save_page()
{
	/* print page: */
	/* input: file */
}

interactive()
{
	/* must walk through file: in runtime, while , check for each word in dictionary */
	/* call save page */
}

help_page()
{
	/* accept a key, then return to main_page */
}

main_page()
{
	/* must take in a command line argument, then direct to help, load file, load dic, or quit */
	/* must accept a file, then parse for dictionary or output file */
}

batch_mode()
{
	// implmenent after having null
}

/* necessary?
int lsh_launch(char **args)
{
	pid_t pid, wpid;
	int status;

	pid = fork();
	if (pid == 0) {	// this is the child process
		if (execvp(args[0],args) == -1) {	// execvp - program name, array
			perror("lsh_launch forking failed\n");
		}
		exit(0);
	} else if (pid<0) {
		perror("lsh_launch forking failed\n");
	} else {
		do {	// parent process: wait until processes are exited, to prompt for input again
			wpid = waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return 1;
}
*/

int lsh_execute(char **args)
{
	if (args[0]==NULL) {
		return 1;
	}

	int n;
	while (args[n] != NULL)
		n++;

	/* Case in which arg entered is only "spellcheck", in which case main page is loaded */
	if (argn==1) {
		printf("%s%s%s",greet(),main_help_text(),shell_prompt());
		main_page();
	}

	/* case in which arg is */
	if (argn==2) {
		/* check that given string is valid input for file */
	}

	/* Case in which arg entered is 1 => If this is a file, enter interactive mode immediately */
	if (argn==3) {
		/* check command line entered is feasible for execution: order of commands, file existence*/
		/* run batch mode, quiet or verbose */
	}


/*
	// count number of args
	int n;
	if (args[0] == NULL) {
		return 1;
	}

	for (i=0; i < lsh_num_builtins(); i++) {
		if (strcmp(args[0], builtin_str[i]) == 0) {
			return(*builtin_func[i])(args);
		}
	} */
	return lsh_launch(args);
}


char **lsh_split_line(char *line)
{
	int bufsize = 64, position=0;
	char **tokens = malloc(bufsize*sizeof(char*));
	char* lsh_tok_delim = " \t\r\n\a"
	char *token;

	if (!tokens) {
		fprintf(stderr, "lsh_split_line: malloc failed\n");
		exit(0);
	}

	token = strtok(line,lsh_tok_delim);
	while (token) {
		tokens[position]=token;
		position++;
		if (position >= bufsize) {
			bufsize += bufsize;
			tokens = realloc(tokens,bufsize*sizeof(char*));
			if (!tokens) {
				fprintf(stderr, "lsh_split_line: realloc failed\n");
				exit(1);
			}
		}

		// returns beginning of next token
		token = strtok(NULL, lsh_tok_delim);
	}
	tokens[position]=NULL;
	return tokens;
}

char *lsh_read_line(void)
{
	char* line=NULL;
	ssize_t bufsize=0;
	// buffer is address of first character position where input string is stored
	// size is address of variable that holds size of input buffer
	// stdin is input file handle
	getline(&line,&bufsize,stdin);
	return line;
}

/* Administer Shell */
int main(int argc, char **argv)
{
	char *line;
	char **args;
	int status;

	do {
		line = lsh_read_line();
		args = lsh_split_line(line);
		status = lsh_execute(args);

		free(line);
		free(args);
	} while (status);

	return 0;
}

#endif
