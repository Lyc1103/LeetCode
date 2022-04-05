#include <stdio.h>

int main()
{
	char filename[100];
	scanf("%s", &filename);
	int len = strlen(filename);
	if (str[len - 1] != '\0')
		str[len] = '\0';
	FILE *pfile1 = fopen(filename, 'r');
	FILE *pfile2 = fopen("output.txt", 'w');
}