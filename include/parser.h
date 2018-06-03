#ifndef INCLUDE_PARSER_H_
#define INCLUDE_PARSER_H_

#include <stdio.h>
#include <stdlib.h>

#define MAXCHAR 1025 ///< Maximum number of characters
#define INITLINE 100 ///< Maximum number of lines
#define READ_BUFFERSIZE 256 ///< Buffer size
#define LSH_TOK_BUFFERSIZE 64 ///< Token buffer size
#define LSH_TOK_DELIM " \t\r\n\a" ///< Token deliminator

/**
 * \file parser.h
 * File parsing functions for the program.
 */

/**
 * \brief Parses a given file.
 *
 * \param filename: File being input.
 * \return Array of strings, each of which represents a line from the file input (returns NULL if file input could not be opened).
 */
char **parse_file(char *filename);


/**
 * \brief Reads the command line and returns a string.
 *
 * \return String representing the command line input.
 */
char *parse_read_line();

/**
 * \brief Reads the command line and return an array of strings.
 *
 * \param line: String from parse_read_line().
 * \return Tokens, each representing a command separated by whitespace.
 */
char **parse_split_line(char *line);

#endif