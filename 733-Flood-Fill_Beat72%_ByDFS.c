#include <stdio.h>
#include <stdlib.h>

void printMatrix(int **mat, int matSize, int matColSize)
{
	for (int i = 0; i < matSize; i++)
	{
		printf("  row%d = [", i);
		for (int j = 0; j < matColSize - 1; j++)
			printf("%d,", mat[i][j]);
		printf("%d]\n", mat[i][matColSize - 1]);
	}
	return;
}

void recursiveFloodFill(int **image, int imageSize, int *imageColSize, int sr, int sc, int newColor, int oldcolor)
{
	if (image[sr][sc] == oldcolor)
	{

		image[sr][sc] = newColor;
		if (sr > 0)
			recursiveFloodFill(image, imageSize, imageColSize, sr - 1, sc, newColor, oldcolor);
		if (sr + 1 < imageSize)
			recursiveFloodFill(image, imageSize, imageColSize, sr + 1, sc, newColor, oldcolor);
		if (sc > 0)
			recursiveFloodFill(image, imageSize, imageColSize, sr, sc - 1, newColor, oldcolor);
		if (sc + 1 < *imageColSize)
			recursiveFloodFill(image, imageSize, imageColSize, sr, sc + 1, newColor, oldcolor);
	}
	return;
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *returnColumnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */
int **floodFill(int **image, int imageSize, int *imageColSize, int sr, int sc, int newColor, int *returnSize, int **returnColumnSizes)
{
	*returnSize = imageSize;
	*returnColumnSizes = (int *)malloc(imageSize * sizeof(int));
	for (int i = 0; i < imageSize; i++)
		(*returnColumnSizes)[i] = imageColSize[i];
	if (image[sr][sc] == newColor)
		return image;
	recursiveFloodFill(image, imageSize, imageColSize, sr, sc, newColor, image[sr][sc]);
	return image;
}

int main()
{
	FILE *pfile;
	if ((pfile = fopen("733.txt", "r")) == NULL)
	{
		puts("Read file could not be opened!");
		return 0;
	}

	char c;
	int **image = (int **)calloc(10, sizeof(int *));
	for (int i = 0; i < 10; i++)
		image[i] = (int *)calloc(10, sizeof(int));
	int imageSize = 0, imageColSize, cnt = 0;
	printf("input: ");
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
			break;
	}
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '[')
		{
			while (!feof(pfile))
			{
				fscanf(pfile, "%d", &image[imageSize][cnt]);
				printf("%d", image[imageSize][cnt]);
				cnt++;
				fscanf(pfile, "%c", &c);
				printf("%c", c);
				if (c == ']')
				{
					imageSize++;
					imageColSize = cnt;
					cnt = 0;
					break;
				}
			}
		}
		else if (c == ']')
			break;
	}
	int sr, sc, newColor, flag = 0;
	while (!feof(pfile))
	{
		fscanf(pfile, "%c", &c);
		printf("%c", c);
		if (c == '=')
			flag++;

		if (flag == 1 && c == '=')
		{
			if (!feof(pfile))
				fscanf(pfile, " %d", &sr);
			printf(" %d", sr);
		}
		else if (flag == 2 && c == '=')
		{
			if (!feof(pfile))
				fscanf(pfile, " %d", &sc);
			printf(" %d", sc);
		}
		else if (flag == 3 && c == '=')
		{
			if (!feof(pfile))
				fscanf(pfile, " %d", &newColor);
			printf(" %d", newColor);
		}
	}
	puts("");

	puts("image =");
	printMatrix(image, imageSize, imageColSize);
	printf("sr = %d, sc = %d, newColor = %d\n\n", sr, sc, newColor);

	int returnSize, *returnColSize;
	int **ret = floodFill(image, imageSize, &imageColSize, sr, sc, newColor, &returnSize, &returnColSize);

	puts("color changed image =");
	printMatrix(ret, returnSize, returnColSize[0]);

	free(image);
	free(ret);
	return 0;
}