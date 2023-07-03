#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "factors.h"

/**
 * factorize - Factorizes the integer n
 * @n: the number to factorize
 *
 * Return: the pair of factors or NULL
 */
pair *factorize(int n)
{
	pair *factors = NULL;
	int i;

	for (i = 2; i <= sqrt(n); i++)
	{
		if (n % i == 0)
		{
			factors = malloc(sizeof(pair));
			factors->x = i;
			factors->y = n / i;
			break;
		}
	}
	return (factors);
}

/**
 * main - Entry point
 * @argc: The command line argument count
 * @argv: The command line argumests
 *
 * Return: Always 0
 */
int main(int argc, char **argv)
{
	FILE *fp = fopen(argv[1], "r");
	char *line = NULL;
	size_t len = 0;
	ssize_t read;
	int n = 0;
	pair *factors = NULL;

	if (argc != 2)
	{
		printf("Usage: factors <file>\n");
		return (1);
	}


	if (fp == NULL)
	{
		perror("fopen");
		return (1);
	}

	while ((read = getline(&line, &len, fp)) != -1)
	{
		n = atoi(line);
		factors = factorize(n);
		if (factors != NULL)
		{
			printf("%d=%d*%d\n", n, factors->y, factors->x);
			free(factors);
		}
	}

	if (line != NULL)
	{
		free(line);
	}
	fclose(fp);
	return (0);
}
