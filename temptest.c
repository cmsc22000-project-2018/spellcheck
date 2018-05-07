/* Text Parsing File
   Jaewan Park
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include "parser.h"
#include "shellstrings.h"
#include "scfunctions.h"

int main()
{
	char* l;
	char** p;
	p = lineparse_file("test.txt");
	int i=0;

	while (p[i]!=NULL) {	// should condition be end of file instead?
		printf("%s",p[i]);
		i++;
	}

	free(p);

	l=read_line();
	p=split_line(l);

	i=0;
	while (p[i]!=NULL) {
		printf("%s\n",p[i]);
		i++;
	}
}
