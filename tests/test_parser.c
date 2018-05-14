#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "parser.h"

/* testing array_resize */
Test(array, resize)
{
    size_t asize = 5;
    char** array = malloc(asize * sizeof(char*));
    size_t j = 0;

    for (; j < asize; j++) array[j] = strdup("I");
    cr_assert_eq(array[3],"I", "array initialization failed");

    if (array == NULL) {
        fprintf(stderr,"test_parser: malloc failed in resize array testing");
    }

    int i = parse_array_resize(array, &asize);
    cr_assert_eq(i, EXIT_SUCCESS, "array resize function failed");
//    cr_assert_eq(array[3], "I", "array resize result failed");
    cr_assert_eq(asize, 10, "array resize size number wrong");
}

/* testing file_parse */
Test(file, parse)
{
    char** array;

    array = parse_file("test_parser.txt");
    cr_assert_not_null(array,"parse_file failed");

    char* c = "It came with my pea sea\n";
    cr_assert_eq(strcmp(array[1], c), 0, "parse_file line read incorrectly");

    int i = 0;
    while (array[i] != NULL) i++;
    cr_assert_eq(i, 16, "parse_file wrong line number");
}


Test(file, parse_resize)
{
    char** array;

    array = parse_file("test_parser2.txt");
    cr_assert_not_null(array,"parse_file failed");

    char* c = "Dipped suddenly down, so suddenly that Alice had not a moment to think\n";
    cr_assert_eq(strcmp(array[30], c), 0, "parse_file line read incorrectly");
    c = "long passage, and the White Rabbit was still in sight, hurrying down it.\n";
    cr_assert_eq(strcmp(array[90], c), 0, "parse_file line read incorrectly");

    int i = 0;
    while (array[i] != NULL) i++;
    cr_assert_eq(i, 147, "parse_file wrong line number");
}

/* testing read_line */
Test(string, read_line)
{

}

/* testing split_line */
Test(string, split_line)
{
    char* c = "./spellcheck -v filename.txt";

}

