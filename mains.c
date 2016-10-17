#include<stdio.h>
#include "features.h"
#include<errno.h>
#include<unistd.h>
#include<string.h>
int main(int argc, char *argv[]) {
	argv[argc] = NULL;
	int i;
	char path[MAX];
		if(argv[1][0] == '-' && argv[1][1] == 'r') {
			if((getcwd(path, sizeof(path))) != NULL)
				i = allfiles(argc, argv, path);/*prints all the lines that are present in all the files in current directory and its 								subdirectories that matches with the given string.*/
			if(i != 0)
				return i; 
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'i') { /*this for -i feature of grep i.e for case of insensitive cases of match */
			i = imatch(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-help") == 0) { /*this for showing menu for grep*/
			help(argc, argv);
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'w') { /*this is different version of match function.It prints line which contain 									whole word and not a substring.  */
			i = wholeword(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'v') { /*this prints the line which doesnt contain the given string. */
			i = invert(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'c') { /*this counts the number of lines which contains the given string. */
			i = matchcount(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'A') {
			i = nextlines(argc, argv); /* this prints the desired number of lines after the line in which first string is found 								*/
			if(i != 0)
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'B') {
			i = beforelines(argc, argv); /* this prints the desired number of lines before the line in which first string is 								found */
			if(i != 0)
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'C') {
			i = neighbourlines(argc, argv); /* this prints the desired number of lines before and after the line in which first 								string is found */
			if(i != 0)
				return i;
		}
		else if(strcmp(argv[1], "-j") == 0 /*|| (strcmp(argv[1], "-v") == 0 && strcmp(argv[2], "-c") == 0)*/) {
			i = invertcount(argc, argv);/*this gives the number of lines which do not match given string.*/
			if(i != 0) 
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'm') {
			i = maxlines(argc, argv);/*this gives the number of required number of lines which match given string.*/
			if(i != 0) 
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'x') {
			i = singleword(argc, argv);/*this only prints the line in which the given single word is present .*/
			if(i != 0) 
				return i;
		}
		else if(argv[1][0] == '-' && argv[1][1] == 'n') {
			i = line_number(argc, argv); /* this prints the line number along with matching lines*/
			if(i != 0)
				return i;
		}
		else if(strcmp(argv[1], "-G") == 0) {
			i = match(argc, argv);  /*taking string as a 2nd argument of main and printing corresponding lines of file where it 							exist*/
			if(i != 0)
				return i; 
		}
		else {
			printf("USE ./mygrep -help for more information.\n");
		} 
	return 0;
}
