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
#define MAX 100000
int match(int, char **);
int imatch(int, char **);
int nextlines(int, char **);
int beforelines(int, char **);
int neighbourlines(int, char **);
int wholeword(int, char **);
int invert(int, char **);
int matchcount(int, char **);
int invertcount(int, char **);
int readline(char *, char *);
int maxlines(int, char **);
int singleword(int, char **);
int line_number(int, char **);
void help(int, char **);
int match_string(int, char **);
int wholeword_count(int, char **);
void list_allfiles(int, char **, const char *, int);
int no_file_name(int, char **);
int with_file_name(int, char **);
int print_file_name(int, char **);
int do_not_print_file_name(int, char **);
void remdupl(double a[], int); 
int neighbourlines2(int, char **);
