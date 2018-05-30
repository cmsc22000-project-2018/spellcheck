#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <stdio.h>
#include <stdlib.h>

/* Parsing Functions:
 * 		Parsing functions receive input from either the command line or a file. In the case of command line input,
 *		parse_read_line and parse_split_line accept the input from the user and split it into tokens.
 * 		In the case of file input, parse_file accepts a filename, opens the file associated with the name and
 *		generates a char** array of lines to correct.
 */

/*
 * parse_file
 * parameter: filename
 *
 * return: pointer to array of strings, each of which represents a line from the given file
 * current limit to each string is 4096 characters, excluding the newline
 * return NULL if file could not be opened
 */
char** parse_file(char* filename);


/* 
 * parse_read_line: read a command line and return a string
 *
 * parameters: none (fgets accepts command line input)
 *
 * return: string representing command line input
 */
char* parse_read_line();

/*
 * parse_split_line: read a command line and return a char** array
 * note that this returns an array, each representing a command separated by a
 * whitespace in the command
 *
 * parameters: string from parse_read_line, which was command line input
 *
 * return: tokens (string), each representing a command separated by a whitespace
 * in the command
 */
char **parse_split_line(char *line);

#endif