#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "parser.h"

/* Note that unit tests for parser_read_line have not been included, as a consequence of command line inputs being required.
 * While future testing will be conducted with shell testing library, note currently that parse_read_line has not
 * resulted in errors when being used in the shell command line */

/* Testing file parsing function */
Test(parser, parse_file)
{
    char** array;

    array = parse_file("test_parser.txt");
    cr_assert_not_null(array,"test_parser: parse_file failed");

    char* c = "Eye halve a spelling chequer\n";
    int i = strncmp(array[0], c, 19);
    cr_assert_eq(i, 0, "parse_file wrong line number, testing line 1");

    c = "My chequer tolled me sew.\n";
    i = strcmp(array[15], c);
    cr_assert_eq(i, 0, "parse_file wrong line number, testing line 16");

    while (array[i] != NULL) i++;
    cr_assert_eq(i, 16, "parse_file wrong total line number");
}

/* parse_file test, with larger functions */ 
Test(parser, parse_file2)   // test for file with 200 lines
{
    char** array;

    array = parse_file("test_parser2.txt");
    cr_assert_not_null(array,"test_parser: parse_file failed");
// compare two strings

    char* c = "CHAPTER I. Down the Rabbit-Hole\n";
    int i = strcmp(array[0] , c);
    cr_assert_eq(i, 0, "parse_file wrong line number, testing line 1");

    c = "Presently she began again. 'I wonder if I shall fall right THROUGH the\n";
    i = strcmp(array[62], c);
    cr_assert_eq(i, 0, "parse_file wrong line number, testing line 16");

    c = "in the common way.\n";
    i = strcmp(array[199], c);
    cr_assert_eq(i, 0, "parse_file wrong line number, testing line 16");

    while (array[i] != NULL) i++;
    cr_assert_eq(i, 200, "parse_file wrong total line number");

}

/* parse_split_line test, returning string array representing each token*/
Test(parser, parse_split_line)
{
    char** array = calloc(20, sizeof(char*));
    char* c = strdup("Quesadillas are delicious");

    array = parse_split_line(c);

    int i = strncmp("are", array[1], 4);

    cr_assert_eq(i, 0, "line not properly split");
}

/* parse_split_line test, returning an array with one item */
Test(parser, parse_split_line1)
{
    char** array = calloc(20, sizeof(char*));
    char* c = strdup("Memento");

    array = parse_split_line(c);

    int i = strncmp("Memento", array[0], 4);

    cr_assert_eq(i, 0, "line not properly split");
}

/* parse_split_line test, returning NULL */
Test(parser, parse_split_line2)    // should return null
{
    char** array = calloc(20, sizeof(char*));
    char* c = strdup("");

    array = parse_split_line(c);

    cr_assert_null(array[0], "parse_split_line should return null");
}
