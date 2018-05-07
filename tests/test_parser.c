/* Text Parsing File
   Jaewan Park
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

int main()
{
	char* l;
	char** p;
	p = lineparse_file("test.txt");
	int i=0;

	while (p[i]!=NULL) {	// should condition be end of file instead?
		printf("%s",p[i]);
		i++
	}

	free(p);

	l=lsh_read_line();
	p=lsh_split_line(l);

	while (p[i]!=NULL) {
		printf("%s",p[i]);
		i++;
	}
}
