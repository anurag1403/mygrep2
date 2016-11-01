/*<GREP command - it searches pattern in given file>
    Copyright (C) 2016  Anurag Kolhe

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    
    for any query call on 9405518625 or e-mail at ID-kolheab15.it@coep.ac.in 
*/
#include<stdio.h>
#include "features.h"
#include<errno.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>
int main(int argc, char *argv[]) {
	argv[argc] = NULL;
	int i, y;
	char path[MAX];
		if(strcmp(argv[1], "-r") == 0) {
			if(argc == 3) {
				if((getcwd(path, sizeof(path))) != NULL) {
					list_allfiles(argc, argv, path, 0);/*prints all the lines that are present in all the files in current directory and its 								subdirectories that matches with the given string.*/
				}
			}
			else {
				for(y = 3; y < argc; y++) {
					list_allfiles(argc, argv, argv[y], 0);
					printf("-----------------------------------------------------------------------------\n");
				}
			} 
		}
		else if((strcmp(argv[1], "-w") == 0 && strcmp(argv[2], "-c") == 0) || (strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-w") == 0))  {
			i = wholeword_count(argc, argv);  /*printing count of lines which contain given string as whole word*/
			if(i != 0)
				return i; 
		}
		else if((strcmp(argv[1], "-c") == 0 && strcmp(argv[2], "-v") == 0) || (strcmp(argv[1], "-v") == 0 && strcmp(argv[2], "-c") == 0)) {
			i = invertcount(argc, argv);/*this gives the number of lines which do not match given string.*/
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-i") == 0) { /*this for -i feature of grep i.e for case of insensitive cases of match */
			i = imatch(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "--help") == 0) { /*this for showing menu for grep*/
			help(argc, argv);
		}
		else if(strcmp(argv[1], "-h") == 0) { /*it prints matching lines without file names.*/
			i = no_file_name(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-H") == 0) { /*it prints matching lines with file names.*/
			i = with_file_name(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-l") == 0) { /*it prints matching lines with file names.*/
			i = print_file_name(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-L") == 0) { /*it prints matching lines with file names.*/
			i = do_not_print_file_name(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-w") == 0) { /*this is different version of match function.It prints line which contain 									whole word and not a substring.  */
			i = wholeword(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-v") == 0) { /*this prints the line which doesnt contain the given string. */
			i = invert(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-c") == 0) { /*this counts the number of lines which contains the given string. */
			i = matchcount(argc, argv);
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-A") == 0) {
			i = nextlines(argc, argv); /* this prints the desired number of lines after the line in which first string is found 								*/
			if(i != 0)
				return i;
		}
		else if(strcmp(argv[1], "-B") == 0) {
			i = beforelines(argc, argv); /* this prints the desired number of lines before the line in which first string is 								found */
			if(i != 0)
				return i;
		}
		else if(strcmp(argv[1], "-C") == 0) {
			i = neighbourlines(argc, argv); /* this prints the desired number of lines before and after the line in which first 								string is found */
			if(i != 0)
				return i;
		}
		else if(strcmp(argv[1], "-m") == 0) {
			i = maxlines(argc, argv);/*this gives the number of required number of lines which match given string.*/
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-x") == 0) {
			i = singleword(argc, argv);/*this only prints the line in which the given single word is present .*/
			if(i != 0) 
				return i;
		}
		else if(strcmp(argv[1], "-n") == 0) {
			i = line_number(argc, argv); /* this prints the line number along with matching lines*/
			if(i != 0)
				return i;
		}
		else if(strcmp(argv[1], "-G") == 0) {
			if(argv[2][0] == '-' && isalpha(argv[2][1]) == 0) {
				i = neighbourlines2(argc, argv);
				if(i != 0)
					return i;
			}
			else {
				i = match(argc, argv);  /*taking string as a 2nd argument of main and printing corresponding lines of file where it 							exist*/
				if(i != 0)
					return i;
			} 
		}
		else if(strcmp(argv[1], "-o") == 0) {
			i = match_string(argc, argv);  /*printing matched substring*/
			if(i != 0)
				return i; 
		}
		else {
			printf("Usage : ./mygrep [OPTIONS] PATTERN [FILE] \nUSE ./mygrep --help for more information.\n");
		} 
	return 0;
}
