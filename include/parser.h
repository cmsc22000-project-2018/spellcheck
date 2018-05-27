#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <stdio.h>
#include <stdlib.h>

/* Parsing Functions for Parsing Input Files */

/*
 * parse_file
 * parameter: filename
 * returns with pointer to array of strings, each of which represent a line in a given file
 * current limit to each string is 4096 characters, excluding the newline
 * return NULL if file could not be opened
 */
char** parse_file(char* filename);

/* Parsing functions for parsing command line inputs */

/* 
 * parse_read_line: read a command line and return a string
 * parameters: none (fgets accepts command line input)
 * return: string representing command line input
 * */
char* parse_read_line();

/*
 * parse_split_line: read a command line and return a char** array
 * note that this returns an array, each representing a command separated by a
 * whitespace in the command
 * parameters: string
 * return: tokens (string), each representing a command separated by a whitespace
 * in the command
 */
char **parse_split_line(char *line);
#endif
