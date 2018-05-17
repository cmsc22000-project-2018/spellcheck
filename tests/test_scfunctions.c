#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scfunctions.h"

/*
underline-misspelled

underline_correctspelling

add_to_badwords

parse_string

correct_line

initialize_bad_words

edit_interactive

*/
Test(scfunctions, underline_misspelled1) {
    char *token = "this is a misspelld word";
    char *underline1 = "misspeld";
    underline_misspelled(token, underline1);
    printf("misspelld\n");
    printf("Expected: a lovely Actual: %s\n", underline1);

}

Test(scfunctions, underline_misspelled2) {
    char *token = "here is a dg";
    char *underline2 = "dg";
    underline_misspelled(token, underline2);
    printf("dg\n");
    printf("Expected: a lovely Actual: %s\n", underline2);
}

Test(scfunctions, underline_misspelled3) {
    char *token = "wat a lovely dy";
    char *underline3 = "wat dy";
    underline_misspelled(token, underline3);
    printf("wat dy\n");
    printf("Expected: wat dy Actual: %s\n", underline3);
}

Test(scfunctions, underline_correct1){
    char *token = "this is a misspelld word";
    char *underline11 = "this is a word";
    underline_misspelled(token, underline11);
    printf("this is a word\n");
    printf("Expected: this is a word Actual: %s\n", underline11);

}

Test(scfunctions, underline_correct2){
    char *token = "here is a dg";
    char *underline22 = "here is a";
    underline_misspelled(token, underline22);
    printf("here is a\n");
    printf("Expected: here is a Actual: %s\n", underline22);
}

Test(scfunctions, underline_correct3){
    char *token = "wat a lovely dy";
    char *underline33 = "a lovely";
    underline_misspelled(token, underline33);
    printf("a lovely\n");
    printf("Expected: a lovely Actual: %s\n", underline33);
}
