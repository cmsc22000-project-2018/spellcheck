#include <stdlib.h>
#include <stdio.h>
#include "dictionary.h"
#include "suggestion.h"

int main() {

    int i;    
    dict_t *d = dict_new();
    if (dict_read(d, "demo_dict.txt") == EXIT_SUCCESS) {
        printf("\ndemo_dict.txt duccessfully read!\n");
    }


    printf("\nThe first 8 words that are within an edit distance of 1 to \"soap\" are:\n");
    char **soap1 = suggestion_list(d, "soap", 1, 10);

    i = 0;
    while (soap1[i] != NULL) {
        printf("%s, ", soap1[i]);
        i++;
    }
    printf("\n");


    printf("\nAll words that are within an edit distance of 2 to \"soap\" are:\n");
    char **soap2 = suggestion_list(d, "soap", 2, 40);

    i = 0;
    while (soap2[i] != NULL) {
        printf("%s, ", soap2[i]);
        i++;
    }
    printf("\n");

    
    printf("\nAll gibberish words in the dictionary that are within an edit distance of 3 to \"longword\" are:\n");
    char **longword = suggestion_list(d, "longword", 3, 40);

    i = 0;
    while (longword[i] != NULL) {
        printf("%s, ", longword[i]);
        i++;
    }
    printf("\n");

    return 0;
}