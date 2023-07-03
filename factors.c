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
pair *factorize(unsigned long long int n)
{
	pair *factors = NULL;
	unsigned long long int i;

	for (i = 2; i <= (n / 2); i++)
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
	unsigned long long int n = 0;
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
		line[strcspn(line, "\n")] = '\0';
		n = strtoull(line, NULL,10);
		factors = factorize(n);
		if (factors != NULL)
		{
			printf("%llu=%llu*%llu\n", n, factors->y, factors->x);
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
