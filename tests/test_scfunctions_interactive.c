#include <criterion/criterion.h>
#include <stdlib.h>
#include <stdbool.h>
#include "scfunctions.h"


void check_underline_misspelled(char* wrong, char* underline, char* expected) {
	underline_misspelled(wrong, underline);
	//printf("%s\n", underline);


	int result = strcmp(underline, expected);

    cr_assert_eq(result, 0, "underline_misspelled_mispelled failed");
}

Test(scfunctions, underline_misspelled) {
	char *wrong = "bool";
	char *underline = (char *)malloc(50);
	strcpy(underline, "");
	char* expected = "^^^^ ";
    check_underline_misspelled(wrong, underline, expected);
}

Test(scfunctions, underline_misspelled2) {
	char *wrong = "hello";
	char *underline = (char *)malloc(50);
	strcpy(underline, "    ");
	char* expected = "    ^^^^^ ";
    check_underline_misspelled(wrong, underline, expected);
}



Test(scfunctions, underline_misspelled3) {
	char *wrong = "wrng";
	char *underline = (char *)malloc(50);
	strcpy(underline, "^^^^ ^^ ");
	char* expected = "^^^^ ^^ ^^^^ ";
    check_underline_misspelled(wrong, underline, expected);
}


void check_add_to_badwords(char *badword, char** badwords) {
	add_to_badwords(badword, badwords);
	int result = -1;
	int i = 0;
	while (badwords[i] != NULL) {
		if (strcmp(badwords[i], badword) == 0) {
			result = 0;
		}
		i++;
	}

	cr_assert_eq(0, result, "check_add_to_badwords failed");

}

Test(scfunctions, check_add_to_badwords) {
	char *badword = "wrod";
	char* badwords[3] = {NULL, NULL, NULL};
	check_add_to_badwords(badword, badwords);

}

