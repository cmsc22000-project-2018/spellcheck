#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"


/* Testing file parsing function */
Test(file,parser)
{
    char** array;

    array = parse_file("test_parser.txt");
    cr_assert_not_null(array,"test_parser: parse_file failed");

// compare two strings

    char* c = "Eye halve a spelling chequer\n";
    int i = strcmp(array[0] , c);
    cr_assert_eq(i, 0, "parse_file wrong line number, testing line 1");

    c = "My chequer tolled me sew.\n";
    i = strcmp(array[15], c);
    cr_assert_eq(i, 0, "parse_file wrong line number, testing line 16");

    while (array[i] != NULL) i++;
    cr_assert_eq(i, 16, "parse_file wrong total line number");
}

Test(file,parser2)
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

Test(string,get_word)
{
//    char* string;
    char** array;

    array = parse_file("test_parser.txt");
//    cr_assert_not_null(array,"test_parser: parse_file failed");
    // test get_word
}


Test(string,read_line)
{
}


Test(string,get)
{
}

