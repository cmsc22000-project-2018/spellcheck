#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "parser.h"
#include "log.c/src/log.h"

/* See parser.h */
char **parse_file(char *filename) {
    FILE *f = fopen(filename, "r");
    log_trace("(parse_file) File '%s' has been opened.", filename);

    if (f == NULL) {
        return NULL;
    }

    // Initialization
    int n = 0;
    int i = INITLINE;
    char str[MAXCHAR];
    char **lines;

    lines = calloc(i, sizeof(char *));
    log_trace("(parse_file) Allocating line array.");
    if (lines == NULL) {
        log_fatal("(parse_file) calloc() failed.");
        exit(0);
    }

    while(fgets(str, MAXCHAR, f) != 0) {
        if (n >= i) {
            log_trace("(parse_file) Reallocating line array, given lengthy file of more than %d lines.", n);
            i += i;

            lines = realloc(lines, i * sizeof (char *));

            if (lines == NULL) {
                log_fatal("(parse_file) realloc() failed.");
                exit(0);
            }
        }

        lines[n] = strdup(str);
        n++;
    }

    lines[n] = NULL;

    fclose(f);
    log_trace("(parse_file) File %s has been closed.", filename);
    return lines;
}

/* See parser.h */
char *parse_read_line() {
    char *input = calloc(READ_BUFFERSIZE, sizeof(char));
    log_trace("(parse_read_line) fgets() input allocated.", input);

    if (input == NULL) {
        log_fatal("(parse_read_line) calloc() failed.");
        exit(1);
    }

    char *cmdlineinput;
    memset(input, '\0', READ_BUFFERSIZE);
    input = fgets(input, READ_BUFFERSIZE, stdin);
    log_trace("(parse_read_line) fgets() input is '%s'.", input);

    if (input == NULL) {
        log_fatal("(parse_read_line) fgets() failed.");
        exit(1);
    }

    int n = strlen(input);
    cmdlineinput = strdup(input);

    if (input[n - 1] == '\n') {
        cmdlineinput[n - 1] = '\0';
    }

    log_trace("(parse_read_line) Freeing input.");
    free(input);

    return cmdlineinput;
}

/* See parser.h */
char **parse_split_line(char *line) {
    int bufsize = LSH_TOK_BUFFERSIZE;
    int position = 0;
    char **tokens = calloc(bufsize, sizeof(char *));
    char *token, **tokens_backup;

    if (!tokens) {
        log_fatal("(parse_split_line) calloc() failed.");
        exit(EXIT_FAILURE);
    }

    /* 
     * Converts input line into an array of strings,
     * each of which represents a line, similar to argc argv in main().
     */
    token = strtok(line, LSH_TOK_DELIM);

    while (token != NULL) {
        log_trace("(parse_split_line) Token: %s", token);
        tokens[position] = token;
        position++;

        if (position >= bufsize) {
            log_trace("(parse_split_line) Reallocating argument array, given lengthy cmd line input with more than %d spaces.", position);
            bufsize += LSH_TOK_BUFFERSIZE;
            tokens_backup = tokens;
            tokens = realloc(tokens, bufsize * sizeof(char *));

            if (!tokens) {
                free(tokens_backup);
                log_fatal("(parse_split_line) realloc() failed.");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, LSH_TOK_DELIM);
    }
    log_trace("(parse_split_line) Number of tokens read: %d", position);

    tokens[position] = NULL;
    return tokens;
}