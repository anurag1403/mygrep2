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
#include"features.h"
#include<string.h>
#include<errno.h>
#include<stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include<unistd.h>
#include<ctype.h>
#define COLOUR_RED "\x1B[31m"
#define COLOUR_VOILET "\x1B[35m" 
#define COLOUR_BLACK "\x1B[0m"
#define COLOUR_GREEN "\x1B[32m"
int count1 = 0;
int count3 = 0;
int for_error = 0;
int readline(char *line, char *argv) { 
	FILE *fp;
	char ch;
	int i, j, k = 0;
	int count = 0;
	fp = fopen(argv, "r");
	if(fp == NULL) {   
		printf("mygrep :%s:\n", argv);
		perror("ERROR:"); 
		for_error++;
		return errno;
	}
	fseek(fp, count1, SEEK_SET); 
	while(1) {
		j = fread(&ch, sizeof(char), 1, fp);
		if(j == 0) {
			i = 0;
			line[k] = '\0';
			break;
		}
		else if(ch == '\n') {
			i = 1;
			count++;
			line[k] = '\0';
			break;
		}
		else {
			line[k] = ch;
			k++;
			count++;
		}
	}
	count1 += count;
	fclose(fp);
	return i;
}		
int readline1(char *line, char *argv) { 
	FILE *fp;
	char ch;
	int i, j, k = 0;
	int count = 0;
	fp = fopen(argv, "r");
	if(fp == NULL) { 
		perror("ERROR:"); 
		for_error++;
		return errno;
	}
	fseek(fp, count3, SEEK_SET); 
	while(1) {
		j = fread(&ch, sizeof(char), 1, fp);
		if(j == 0) {
				i = 0;
				line[k] = '\0';
				break;
			}
		else if(ch == '\n') {
			i = 1;
			count++;
			line[k] = '\0';
			break;
		}
		
		else {
			line[k] = ch;
			k++;
			count++;
		}
	}
	count3 += count;
	fclose(fp);
	return i;
}							
int match(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		int arr[1000];
		line = (char *)malloc(sizeof(char) * MAX);
		int i = 0, j, k, line1, file1, max, flag, l, m, index;
		static int flag1 = 0;
		for(l = 0; l < 1000; l++)
			arr[l] = -1;				
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			m = 0;
			index = 0;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
	 		max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						arr[m++] = i;
						arr[m++] = k - 1;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(flag == 1) {
				if(argc > 4)
					printf("%s%s:", COLOUR_VOILET, argv[y]);
				for(l = 0; l < line1; l++) {
					if((l >= arr[index]) && (l <= arr[index + 1])) {
						printf("%s%c",COLOUR_RED, line[l]);
					} 
					else 
						printf("%s%c", COLOUR_BLACK, line[l]);
					if(l == arr[index + 1])
						index += 2;
				}
				printf("\n");
			}
		}
		flag1++;	
	}
	return 0;
}
int imatch(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char *)malloc(sizeof(char) * MAX);
		int arr[1000]; 
		int i, j, k, line1, file1, max, flag = 0, ascii, l, m , index;
		static int flag1 = 0;
		for(l = 0; l < 1000; l++)
			arr[l] = -1;				
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			m = 0;
			index = 0;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					ascii = line[k] - argv[2][j]; 
					if(ascii == 0 || ascii == -32 || ascii == 32) {
						k++;
					}
					else
						break;
					if(j == (file1 - 1)) {
						arr[m++] = i;
						arr[m++] = k - 1;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(flag == 1) {
				if(argc > 4)
					printf("%s%s:", COLOUR_VOILET, argv[y]);
				for(l = 0; l < line1; l++) {
					if((l >= arr[index]) && (l <= arr[index + 1])) {
						printf("%s%c",COLOUR_RED, line[l]);
					} 
					else 
						printf("%s%c", COLOUR_BLACK, line[l]);
					if(l == arr[index + 1])
						index += 2;
				}
				printf("\n");
			}
		}
		flag1++;
	}
	return 0;
}
void remdupl(double a[], int size) {
	int b[99];
	int k = 0, sizek = 0, i, j, flag = 0, t, m, x;
	for(i = 0; i < (size - 1); i++) {
		for(j = (i + 1); j < size; j++) {
			if(a[i] == a[j]) {
			
				for(x = 0; x < sizek; x++) {
					if(b[x] == j) {
						flag = 1;
						break;
					} 
				}
				if(flag == 0) {
					b[k] = j;
					k++;
					sizek++;
				}
			}			
		}
	}
	for(i = 0; i < (k - 1); i++) {
		for(j = i + 1; j < k; j++) {
			if(b[i] > b[j]) {
				t = b[j];
				b[j] = b[i];
				b[i] = t;
			}
		}
	}			
	k = 0;
	while(k < sizek) {
		j = b[k];
		while(j < (size - 1)) {
			a[j] = a[j + 1];
			j++;
		}
		size--;
		m = k;
		while(m < sizek) {
			b[m]--;
			m++;
		}
		k++;
	}	
}
int nextlines(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		double ind[MAX];
		int i, j, k, line1, file1, max, flag = 0, ar2, ar3, l = 0, lineno1 = 0, lineno = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		ar2 = atoi(argv[2]);
		if(ar2 < 0) {
			printf("mygrep :%d: invalid context length argument\n", ar2);
			return EINVAL;
		}   
		ar3 = ar2;
		while((readline(line, argv[y])) != 0) {
			count3 = count1;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[3]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[3][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			lineno++;
			if(flag == 1) {
				lineno1 = lineno;
				ind[l++] = lineno1++;
				while((readline1(line, argv[y]) != 0) && ar2 > 0) {
					ind[l++] = lineno1++;
					ar2--;
				}
			}
			ar2 = ar3;
		}
		lineno = 0;
		count1 = 0;
		remdupl(ind, l);
		while((readline(line, argv[y])) != 0) {
			lineno++;
			for(j = 0; j < l; j++) {
				if(lineno == ind[j]) {
					if(argc > 5)
						printf("%s:", argv[y]);
					printf("%s\n", line);
					break;
				}
			}
		} 
		flag1++;
	}
	return 0;
}
int beforelines(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(MAX);
		double ind[MAX];
		int i, j, k, line1, file1, max, flag = 0, ar2, ar3, l = 0, lineno = 0, lineno1 = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		ar2 = atoi(argv[2]);
		if(ar2 < 0) {
			printf("mygrep :%d: invalid context length argument\n", ar2);
			return EINVAL;
		}
		ar3 = ar2;
		while((readline(line, argv[y])) != 0) {
			count3 = count1;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[3]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[3][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			lineno++;
			if(flag == 1) {
				lineno1 = lineno;
				ind[l++] = lineno1--;
				if(lineno1 < 1)
					lineno1++;
				while(ar2 > 0) {
					if(lineno1 < 1)
						lineno1++;
					ind[l++] = lineno1--;
					ar2--;
				}
			}
			ar2 = ar3;				
		}
		lineno = 0;
		count1 = 0;
		remdupl(ind, l);
		while((readline(line, argv[y])) != 0) {
			lineno++;
			for(j = 0; j < l; j++) {
				if(lineno == ind[j]) {
					if(argc > 5)
						printf("%s:", argv[y]);
					printf("%s\n", line);
					break;
				}
			}
		}
		flag1++;
	}
	return 0;
}	
int neighbourlines(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(MAX);
		double ind[MAX];
		int i, j, k, line1, file1, max, flag = 0, ar2, ar3, l = 0, lineno = 0, lineno1 = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		ar2 = atoi(argv[2]);
		if(ar2 < 0) {
			printf("mygrep :%d: invalid context length argument\n", ar2);
			return EINVAL;
		}
		ar3 = ar2;
		while((readline(line, argv[y])) != 0) {
			count3 = count1;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[3]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[3][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
					}
				}
				if(flag == 2)
					flag--;
			}
			lineno++;
			if(flag == 1) {
				lineno1 = lineno;
				ind[l++] = lineno1--;
				if(lineno1 < 1)
					lineno1++;
				while(ar2 > 0) {
					if(lineno1 < 1)
						lineno1++;
					ind[l++] = lineno1--;
					ar2--;
				}
				ar2 = ar3;
				lineno1 = lineno;
				ind[l++] = lineno1++;
				while((readline1(line, argv[y]) != 0) && ar2 > 0) {
					ind[l++] = lineno1++;
					ar2--;
				}
			}
			ar2 = ar3;
		}
		lineno = 0;
		count1 = 0;
		remdupl(ind, l);
		while((readline(line, argv[y])) != 0) {
			lineno++;
			for(j = 0; j < l; j++) {
				if(lineno == ind[j]) {
					if(argc > 5)
						printf("%s:", argv[y]);
					printf("%s\n", line);
					break;
				}
			}
		}
		flag1++;
	}
	return 0;
}	
int wholeword(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, l, m, index;
		int arr[1000];
		for(l = 0; l < 1000; l++)
			arr[l] = -1;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			index = 0;
			flag = 0;
			m = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1) && isalnum(line[k]) == 0 && isalnum(line[i-1]) == 0 && line[k] != '_' && line[i-1] != '_') {
						arr[m++] = i;
						arr[m++] = k-1;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(flag == 1) {
				if(argc > 4)
					printf("%s%s:", COLOUR_VOILET, argv[y]);
				for(l = 0; l < line1; l++) {
					if((l >= arr[index]) && (l <= arr[index + 1])) {
						printf("%s%c",COLOUR_RED, line[l]);
					} 
					else 
						printf("%s%c", COLOUR_BLACK, line[l]);
					if(l == arr[index + 1])
						index += 2;
				}
				printf("\n");
			}
		}
		flag1++;
	}
	return 0;
}
int invert(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, count2, l;
		static int flag1 = 0;
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}	
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			count2 = 0;
			l = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
						count2++;
						break;
					}
				}
				if(flag == 1) {
					flag = 0;
					break;
				}
			}	
			if(count2 == 0) {
				if(argc > 4)
					printf("%s%s:", COLOUR_VOILET, argv[y]);
				for(l = 0; l < line1; l++) 
					printf("%s%c", COLOUR_BLACK, line[l]);
				printf("\n");
			}	
		}	
		flag1++;
	}
	return 0;
}
int matchcount(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, count2 = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			line1 = strlen(line);
			file1 = strlen(argv[2]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						count2++;
						flag++;
						break;
					}
				}
				if(flag == 1) {
					flag = 0;
					break;
				}
			}
		}
		if(argc > 4)
			printf("%s%s:", COLOUR_VOILET, argv[y]);
		printf("%s%d\n",COLOUR_BLACK, count2);
		flag1++;
	}
	return 0;
}
int invertcount(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, count2, number = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			count2 = 0;
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			line1 = strlen(line);
			file1 = strlen(argv[3]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[3][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
						count2++;
						break;
					}
				}
				if(flag == 1) {
					flag = 0;
					break;
				}
			}
			if(count2 == 0)
				number++;
		}	
		if(argc > 5)
			printf("%s%s:", COLOUR_VOILET, argv[y]); 
		printf("%s%d\n",COLOUR_BLACK, number);
		flag1++;
	}
	return 0;
}

void list_allfiles(int argc, char *argv[], const char *name, int depth) {
	DIR *dir;
	struct dirent *entry;
	int i, j, k, line1, file1, max, flag = 0;
	char *line;
	char path[1024];
	line = (char*)malloc(MAX);
	if(!(dir = opendir(name))) {
    		perror("ERROR:");
        	return;
    	}
    	if(!(entry = readdir(dir)))
        	return;
	do {
        	if(entry->d_type == DT_DIR) {
            		int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            		path[len] = 0;
            		if(strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                		continue;
            		printf("%*s%s[%s]\n", depth * 2, "", COLOUR_GREEN, entry->d_name);
            		list_allfiles(argc, argv, path, depth + 1);
        	}
        	else {
        		printf("%*s-%s%s:\n", depth * 2, "", COLOUR_VOILET, entry->d_name);
            		int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
            		path[len] = 0;
            		count1 = 0;
            		while((readline(line, path)) != 0) {
	    			line1 = strlen(line);
				file1 = strlen(argv[2]);
				max = line1 - file1 + 1;
				for(i = 0; i < max; i++) {
					k = i;
					for(j = 0; j < file1; j++) {
						if(line[k] != argv[2][j]) {
							break;
						}
						k++;
						if(j == (file1 - 1)) {
							printf("%*s%s%s:%s%s\n", depth * 4, "", COLOUR_VOILET, entry->d_name, COLOUR_BLACK, line);
							flag++;
							break;
						}
					}
					if(flag == 1) {
						flag = 0;
						break;
					}
				}
			}
		}	
    }while((entry = readdir(dir)) != NULL);
    closedir(dir);
}
int maxlines(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, ar2, l, index, m;
		static int flag1 = 0;
		int arr[1000];
		for(l = 0; l < 1000; l++)
			arr[l] = -1;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		ar2 = atoi(argv[2]);
		if(ar2 < 0) {
			while((readline(line, argv[y])) != 0) {
				if(for_error == 1) {
					for_error = 0;
					break;
				}
				m = 0;
				index = 0;
				flag = 0;
				line1 = strlen(line);
				file1 = strlen(argv[3]);
	 			max = line1 - file1 + 1;
				for(i = 0; i < max; i++) {
					k = i;
					for(j = 0; j < file1; j++) {
						if(line[k] != argv[3][j]) {
							break;
						}
						k++;
						if(j == (file1 - 1)) {
							arr[m++] = i;
							arr[m++] = k - 1;
							flag++;
						}
					}
					if(flag == 2) {
						flag--;
					}
				}
				if(flag == 1) {
					if(argc > 5)
						printf("%s%s:", COLOUR_VOILET, argv[y]);
					for(l = 0; l < line1; l++) {
						if((l >= arr[index]) && (l <= arr[index + 1])) {
							printf("%s%c",COLOUR_RED, line[l]);
						} 
						else 
							printf("%s%c", COLOUR_BLACK, line[l]);
						if(l == arr[index + 1])
							index += 2;
					}
					printf("\n");
				}
			}
		}
		else {
			while((readline(line, argv[y])) != 0) {
				flag = 0;
				index = 0;
				m = 0;
				line1 = strlen(line);
				file1 = strlen(argv[3]);
				max = line1 - file1 + 1;
				for(i = 0; i < max; i++) {
					k = i;
					for(j = 0; j < file1; j++) {
						if(line[k] != argv[3][j]) {
							break;
						}
						k++;
						if(j == (file1 - 1)) {
							arr[m++] = i;
							arr[m++] = k - 1;
							flag++;
						}
					}
					if(flag == 2) {
						flag--;
					}
				}
				if(flag == 1 && ar2 > 0) {
					if(argc > 5)
						printf("%s%s:", COLOUR_VOILET, argv[y]);
					for(l = 0; l < line1; l++) {
						if((l >= arr[index]) && (l <= arr[index + 1])) {
							printf("%s%c",COLOUR_RED, line[l]);
						} 
						else 
						printf("%s%c", COLOUR_BLACK, line[l]);
						if(l == arr[index + 1])
							index += 2;
					}
					printf("\n");
					ar2--;
				}
			}	
		}
		flag1++;
	}
	return 0;
}
int singleword(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, l, m, index;
		int arr[1000];
		for(l = 0; l < 1000; l++)
			arr[l] = -1;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			index = 0;
			flag = 0;
			m = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1) && line[k] == '\0' && i == 0) {
						arr[m++] = i;
						arr[m++] = k-1;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(flag == 1) {
				if(argc > 4)
					printf("%s%s:", COLOUR_VOILET, argv[y]);
				for(l = 0; l < line1; l++) {
					if((l >= arr[index]) && (l <= arr[index + 1])) {
						printf("%s%c",COLOUR_RED, line[l]);
					} 
					else 
						printf("%s%c", COLOUR_BLACK, line[l]);
					if(l == arr[index + 1])
						index += 2;
				}
				printf("\n");
			}
		}
		flag1++;
	}
	return 0;
}
int line_number(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		int arr[1000];
		line = (char *)malloc(sizeof(char) * MAX);
		int i = 0, j, k, line1, file1, max, flag, l, m, index, lineno = 0;
		static int flag1 = 0;
		for(l = 0; l < 1000; l++)
			arr[l] = -1;				
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			m = 0;
			index = 0;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
	 		max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						arr[m++] = i;
						arr[m++] = k - 1;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			lineno++;
			if(flag == 1) {
				if(argc > 4)
					printf("%s%s:", COLOUR_VOILET, argv[y]);
				printf("%s%d:", COLOUR_GREEN, lineno);
				for(l = 0; l < line1; l++) {
					if((l >= arr[index]) && (l <= arr[index + 1])) {
						printf("%s%c", COLOUR_RED, line[l]);
					} 
					else 
						printf("%s%c", COLOUR_BLACK, line[l]);
					if(l == arr[index + 1])
						index += 2;
				}
				printf("\n");
			}
		}
		flag1++;	
	}
	return 0;
}
void help(int argc, char *argv[]) {
	FILE *fp;
	fp = fopen("help.txt", "r");
	char ch;
	while((fscanf(fp, "%c", &ch)) != -1) {
		printf("%c", ch);
	}
	fclose(fp);
}
int match_string(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char *)malloc(sizeof(char) * MAX);
		int i = 0, j, k, line1, file1, max, flag;
		static int flag1 = 0;				
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
	 		max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(flag == 1) {
				if(argc > 4)
					printf("%s%s:", COLOUR_VOILET, argv[y]);
				printf("%s%s",COLOUR_RED, argv[2]);
				printf("\n");
			}
		}
		flag1++;	
	}
	return 0;
}
int wholeword_count(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, count2 = 0, number = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[3]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[3][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1) && isalnum(line[k]) == 0 && isalnum(line[i-1]) == 0 && line[k] != '_' && line[i-1] != '_') {
						count2++;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(count2 != 0) {
				number++;
				count2 = 0;
			}
		}
		if(argc > 5)
		printf("%s%s:", COLOUR_VOILET, argv[y]);
		printf("%s%d\n",COLOUR_BLACK, number);
		flag1++;
	}
	return 0;
}
int no_file_name(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		int arr[1000];
		line = (char *)malloc(sizeof(char) * MAX);
		int i = 0, j, k, line1, file1, max, flag, l, m, index;
		static int flag1 = 0;
		for(l = 0; l < 1000; l++)
			arr[l] = -1;				
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			m = 0;
			index = 0;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
	 		max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						arr[m++] = i;
						arr[m++] = k - 1;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(flag == 1) {
				for(l = 0; l < line1; l++) {
					if((l >= arr[index]) && (l <= arr[index + 1])) {
						printf("%s%c",COLOUR_RED, line[l]);
					} 
					else 
						printf("%s%c", COLOUR_BLACK, line[l]);
					if(l == arr[index + 1])
						index += 2;
				}
				printf("\n");
			}
		}
		flag1++;	
	}
	return 0;
}
int with_file_name(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		int arr[1000];
		line = (char *)malloc(sizeof(char) * MAX);
		int i = 0, j, k, line1, file1, max, flag, l, m, index;
		static int flag1 = 0;
		for(l = 0; l < 1000; l++)
			arr[l] = -1;				
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			m = 0;
			index = 0;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[2]);
	 		max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						arr[m++] = i;
						arr[m++] = k - 1;
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
			if(flag == 1) {
				printf("%s%s:", COLOUR_VOILET, argv[y]);
				for(l = 0; l < line1; l++) {
					if((l >= arr[index]) && (l <= arr[index + 1])) {
						printf("%s%c",COLOUR_RED, line[l]);
					} 
					else 
						printf("%s%c", COLOUR_BLACK, line[l]);
					if(l == arr[index + 1])
						index += 2;
				}
				printf("\n");
			}
		}
		flag1++;	
	}
	return 0;
}
int print_file_name(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char *)malloc(sizeof(char) * MAX);
		int i = 0, j, k, line1, file1, max, flag = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			line1 = strlen(line);
			file1 = strlen(argv[2]);
	 		max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
		}
		if(flag == 1) 
			printf("%s%s\n", COLOUR_VOILET, argv[y]);
		flag1++;	
	}
	return 0;
}
int do_not_print_file_name(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
		char *line;
		line = (char *)malloc(sizeof(char) * MAX);
		int i = 0, j, k, line1, file1, max, flag;
		static int flag1 = 0;				
		if(flag1 == 1) {
			count1 = 0;
			flag1 = 0;
		}
		while((readline(line, argv[y])) != 0) {
			if(for_error == 1) {
				for_error = 0;
				break;
			}
			line1 = strlen(line);
			file1 = strlen(argv[2]);
	 		max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[2][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
					}
				}
				if(flag == 2) {
					flag--;
				}
			}
		}
		if(flag != 1) 
			printf("%s%s\n", COLOUR_VOILET, argv[y]);
		flag1++;	
	}
	return 0;
}
int neighbourlines2(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(MAX);
		double ind[MAX];
		int i, j, k, line1, file1, max, flag = 0, ar2, ar3, l = 0, lineno = 0, lineno1 = 0;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		ar2 = atoi(argv[2]);
		if(ar2 < 0)
			ar2 = ar2 * -1;
		ar3 = ar2;
		while((readline(line, argv[y])) != 0) {
			count3 = count1;
			flag = 0;
			line1 = strlen(line);
			file1 = strlen(argv[3]);
			max = line1 - file1 + 1;
			for(i = 0; i < max; i++) {
				k = i;
				for(j = 0; j < file1; j++) {
					if(line[k] != argv[3][j]) {
						break;
					}
					k++;
					if(j == (file1 - 1)) {
						flag++;
					}
				}
				if(flag == 2)
					flag--;
			}
			lineno++;
			if(flag == 1) {
				lineno1 = lineno;
				ind[l++] = lineno1--;
				if(lineno1 < 1)
					lineno1++;
				while(ar2 > 0) {
					if(lineno1 < 1)
						lineno1++;
					ind[l++] = lineno1--;
					ar2--;
				}
				ar2 = ar3;
				lineno1 = lineno;
				ind[l++] = lineno1++;
				while((readline1(line, argv[y]) != 0) && ar2 > 0) {
					ind[l++] = lineno1++;
					ar2--;
				}
			}
			ar2 = ar3;
		}
		lineno = 0;
		count1 = 0;
		remdupl(ind, l);
		while((readline(line, argv[y])) != 0) {
			lineno++;
			for(j = 0; j < l; j++) {
				if(lineno == ind[j]) {
					if(argc > 5)
						printf("%s:", argv[y]);
					printf("%s\n", line);
					break;
				}
			}
		}
		flag1++;
	}
	return 0;
}	
















