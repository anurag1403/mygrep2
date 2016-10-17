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
int nextlines(int argc, char *argv[]) {
	int y;
	for(y = 4; argv[y] != NULL; y++) {
		char *line;
		line = (char*)malloc(sizeof(char) * MAX);
		int i, j, k, line1, file1, max, flag = 0, ar2, ar3, l, m, index;
		static int flag1 = 0;
		if(flag1 == 1) {
			flag1 = 0;
			count1 = 0;
		}
		int arr[1000];
		for(l = 0; l < 1000; l++)
			arr[l] = -1;
		ar2 = atoi(argv[2]);
		ar3 = ar2;
		while((readline(line, argv[y])) != 0) {
			count3 = count1;
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
				while((readline1(line, argv[y]) != 0) && ar2 > 0) {
					printf("%s%s:", COLOUR_VOILET, argv[y]);
					printf("%s%s\n", COLOUR_BLACK, line);
					ar2--;
				}
			}
			ar2 = ar3;
		}
		flag1++;
	}
	return 0;
}
int beforelines(int argc, char *argv[]) {
	char *newl, *line[100000];
	int i, j, k, line1, file1, max, flag = 0, ar2, l = 0, m = 100000, n;
	FILE *fp;
	fp = fopen(argv[4], "r");
	if(fp == NULL) { 
		perror("ERROR:");
		return errno;
	}
	while(m > 0) {
		line[l] = (char*)malloc(sizeof(char) * 100000);
		l++;
		m--;
	}
	line[l] = (char*)malloc(sizeof(char) * 100000);
	l = 0;
	rewind(fp);
	ar2 = atoi(argv[2]);
	while((fgets(line[l], 100000, fp)) != NULL) {
		newl = strchr(line[l], '\n');
		*newl = '\0';
		line1 = strlen(line[l]);
		file1 = strlen(argv[3]);
		max = line1 - file1 + 1;
		for(i = 0; i < max; i++) {
			k = i;
			for(j = 0; j < file1; j++) {
				if(line[l][k] != argv[3][j]) {
					break;
				}
				k++;
				if(j == (file1 - 1)) {
					flag++;
					break;
				}
			}
			if(flag == 1) {
				flag = 2;
				break;
			}
		}
		if(flag == 2)
			break;
		l++;
	}
	n = l - ar2;
	if(n > 0) {
		while(n <= l) {
			printf("%s : %s\n", argv[4], line[n]);
			n++;
		}
	}
	else {
		n = 0;
		while(n <= l) {
			printf("%s : %s\n", argv[4], line[n]);
			n++;
		}
	}
	fclose(fp);
	return 0;
}
int neighbourlines(int argc, char *argv[]) {
	char *newl, *line[100000];
	int i, j, k, line1, file1, max, flag = 0, ar2, l = 0, m = 100000, n;
	FILE *fp;
	fp = fopen(argv[4], "r");
	if(fp == NULL) { 
		perror("ERROR:");
		return errno;
	}
	while(m > 0) {
		line[l] = (char*)malloc(sizeof(char) * 100000);
		l++;
		m--;
	}
	l = 0;
	rewind(fp);
	ar2 = atoi(argv[2]);
	while((fgets(line[l], 100000, fp)) != NULL) {
		newl = strchr(line[l], '\n');
		*newl = '\0';
		line1 = strlen(line[l]);
		file1 = strlen(argv[3]);
		max = line1 - file1 + 1;
		for(i = 0; i < max; i++) {
			k = i;
			for(j = 0; j < file1; j++) {
				if(line[l][k] != argv[3][j]) {
					break;
				}
				k++;
				if(j == (file1 - 1)) {
					flag++;
					break;
				}
			}
			if(flag == 1) {
				flag = 2;
				break;
			}
		}
		if(flag == 2)
			break;
		l++;
	}
	n = l - ar2;
	if(n > 0) {
		while(n <= l) {
			printf("%s : %s\n", argv[4], line[n]);
			n++;
		}
		while(((fgets(line[l + 1], MAX, fp)) != NULL) && ar2 > 0) {
			newl = strchr(line[l + 1], '\n');
			*newl = '\0';
			printf("%s : %s\n", argv[4], line[l + 1]);
			ar2--;
		}
	}
	else {
		n = 0;
		while(n <= l) {
			printf("%s : %s\n", argv[4], line[n]);
			n++;
		}
		while(((fgets(line[l + 1], MAX, fp)) != NULL) && ar2 > 0) {
			newl = strchr(line[l + 1], '\n');
			*newl = '\0';
			printf("%s : %s\n", argv[4], line[l + 1]);
			ar2--;
		}
	}
	fclose(fp);
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
		printf("%s%s:", COLOUR_VOILET, argv[y]);
		printf("%s%d\n",COLOUR_BLACK, count2);
		flag1++;
	}
	return 0;
}
int invertcount(int argc, char *argv[]) {
	int y;
	for(y = 3; argv[y] != NULL; y++) {
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
			if(count2 == 0)
				number++;
		}	
		printf("%s%s:", COLOUR_VOILET, argv[y]); 
		printf("%s%d\n", COLOUR_BLACK, number);
		flag1++;
	}
	return 0;
}
int allfiles(int argc, char *argv[], char *path) {
	char *newl;
	char line[MAX];
	int i, j, k, line1, file1, max, flag = 0;
	FILE *fp;
	DIR* dir;
	struct dirent *dirEntry;
	struct stat inode;
	//char name[MAX];
	dir = opendir(path);
	if (dir == 0) {
		perror ("ERROR:");
		return errno;
	}
	while((dirEntry = readdir(dir)) != 0) {
		//sprintf(name,"%s%s", path, dirEntry->d_name); 
		lstat (dirEntry->d_name, &inode);
		//printf("%s\n",dirEntry->d_name);
		if (S_ISREG(inode.st_mode)) {
			printf("file:%s\n",dirEntry->d_name);
			fp = fopen(dirEntry->d_name, "r");
			if(fp == NULL) { 
				perror("ERROR:");
				return errno;
			}
			while((fgets(line, MAX, fp)) != NULL) {
				newl = strchr(line, '\n');
				*newl = '\0';
				line1 = strlen(line);
				file1 = strlen(argv[1]);
				max = line1 - file1 + 1;
				for(i = 0; i < max; i++) {
					k = i;
					for(j = 0; j < file1; j++) {
						if(line[k] != argv[1][j]) {
							break;
						}
						k++;
						if(j == (file1 - 1)) {
							printf("%s : %s\n", dirEntry->d_name, line);
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
			fclose(fp);
		}
		else if (S_ISDIR(inode.st_mode)) {
			 printf("dir:%s\n",dirEntry->d_name);
		}
	}
	closedir(dir);
	return 0;
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
			if(flag == 1) {
				lineno++;
				printf("%s%s:%s%d:", COLOUR_VOILET, argv[y], COLOUR_GREEN, lineno);
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
	











