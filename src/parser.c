#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "parser.h"
#include "log.c/src/log.h"

#define MAXCHAR 4096
#define INITLINE 100
#define READ_BUFFERSIZE 256
#define LSH_TOK_BUFFERSIZE 64
#define LSH_TOK_DELIM " \t\r\n\a"

/* Parsing Functions for Parsing Input Files */

/* returns with pointer to array of strings, each of which represent a line in a given file */
/* current limit to each string is 1000 characters */
/* return NULL if file could not be opened */
char** parse_file(char* filename)
{
    FILE *f = fopen(filename, "r");
    log_trace("file %s has been opened", filename);

    if (f == NULL) {
        return NULL;
    }

    // initialization
    int n = 0;
    int i = INITLINE;
    char str[MAXCHAR];
    char** lines;

    lines = calloc(i, sizeof(char*));
    log_trace("allocating line array");
    if (lines == NULL) {
        fprintf(stderr, "lineparse_file: calloc failed\n");
        exit(0);
    }

    while(fgets(str, MAXCHAR, f) != 0) {

        if (n >= i) {
            log_info("reallocating line array, given lengthy file of more than %d lines", n);
            i += i;

            lines = realloc(lines, i * sizeof (char*));

            if (lines == NULL) {
                fprintf(stderr, "lineparse_file: realloc failed\n");
                exit(0);

            }
        }

        lines[n] = strdup(str);
        n++;
    }

    log_trace("%d lines read", n);
    lines[n] = NULL;

    fclose(f);
    log_trace("file %s has been closed", filename);
    return lines;
}

/* Parsing functions for parsing command line inputs */
/* read a command line and return a string */
char* parse_read_line()
{
    char* input = calloc(READ_BUFFERSIZE, sizeof(char));
    log_trace("fgets input allocated", input);

    if (input == NULL) {
        log_trace("calloc failed");
        fprintf(stderr, "read_line: calloc failed");
        exit(1);
    }

    char* cmdlineinput;
    memset(input, '\0', READ_BUFFERSIZE);
    input = fgets(input, READ_BUFFERSIZE, stdin);
    log_trace("fgets input is: %s", input);

    if (input == NULL) {
        fprintf(stderr, "read_line: fgets failed");
        exit(1);
    }

    int n = strlen(input);
    cmdlineinput = strdup(input);
    if (input[n-1] == '\n')
        cmdlineinput[n-1] = '\0';

    log_trace("freeing input");
    free(input);

    return cmdlineinput;
}

/*
   reference: https://github.com/brenns10/lsh/blob/master/src/main.c
   Split a line into tokens (very naively), and return null-terminated array of tokens.
 */
char **parse_split_line(char *line)
{
    int bufsize = LSH_TOK_BUFFERSIZE;
    int position = 0;
    char **tokens = calloc(bufsize, sizeof(char*));
    char *token, **tokens_backup;

    if (!tokens) {
        log_trace("calloc failed");
        fprintf(stderr, "parse_split_line: calloc error\n");
        exit(EXIT_FAILURE);
    }

    // convert input line into an array of strings, each of which represents a line. similar to argc argv in main
    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL) {

        log_trace("token: %s", token);
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            log_info("reallocating argument array, given lengthy cmd line input with more than %d spaces", position);
            bufsize += LSH_TOK_BUFFERSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char*));

            if (!tokens) {
                free(tokens_backup);
                fprintf(stderr, "parse_split_line: realloc error\n");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    log_trace("number of tokens read: %d", position);


    tokens[position] = NULL;
    return tokens;
}
