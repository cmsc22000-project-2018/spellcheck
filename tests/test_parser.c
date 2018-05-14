#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>

Test(array,resize)
{
    size_t asize = 5;
    char** array = malloc(5 * sizeof(char*));
    if (array == NULL) {
        printf(stderr,"test_parser: malloc failed in resize array testing");
    }
    array_resize(array,5);

    cr_assert_eq(asize,10,"array resize: resize failed");
}

Test(file,parse)
{
    char** array;

    array = parse_file("test_parser.txt");
    cr_assert_not_null(array,"test_parser: parse_file failed");

// compare two strings

    int i = 0;
    while (array[i] != NULL) i++;
    cr_asser_eq(i, 16, "test_parser: parse_file wrong line number");
}

Test(file,parse_resize)
{
    char** array;

    array = parse_file("test_parser2.txt");
    cr_assert_not_null(array,"test_parser: parse_file failed");

    int i = 0;
    while (array[i] != NULL) i++;
    cr_asser_eq(i, 147, "test_parser: parse_file wrong line number");

}

Test(string,get_word)
{
    char* string;
    char** array;

    array = parse_file("test_parser.txt");
    cr_assert_not_null(array,"test_parser: parse_file failed");

    // test get_word
}


Test(string,read_line)
{
}


Test(string,get)
{
}

