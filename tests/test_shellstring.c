#include <criterion/criterion.h>
#include <stdio.h>
#include <stdlib.h>
#include "shellstrings.h"

int counter;

int strings_main()
{
    printf("**Testing Shell String Library\n\n");
    counter=0;

    printf("\n\n**Shell Prompt, printed in Bold White:\n");
    shell_prompt();
    counter++;

    printf("\n\n**Intro text. Header in bold white, directions in blue, commands in normal text\n");
    shell_intro();
    counter++;

    printf("\n\n**Save text. File editing success message in green, commands in normal text\n");
    shell_save();
    counter++;

    printf("\n\n**Shell Error text. Prints out \"=> ERROR\" in red\n");
    shell_error("[This is where an error message would be printed]");
    counter++;

    printf("\n\n**Shell Usage Help text, printed in case of wrong command line input\n");
    shell_usage();
    counter++;

    printf("\n\n**Shell Input confirmation message\n");
    shell_input("[file_name]", "[usage]");
    counter++;

    printf("\n\n**Shell outro message\n");
    shell_outro();
    counter++;

    printf("EXPECTED VALUE OF NUMBER OF PRINTED STRINGS: 7\n");
    printf("TOTAL NUMBER OF STRINGS PRINTED SUCCESSFULLY: %d\n", counter);

    return counter;
}


Test(strings,print)
{
    int i = strings_main();

    cr_assert_eq(i, 7, "Not all strings printed");
}
