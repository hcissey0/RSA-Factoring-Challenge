#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int ac, char **av)
{
	FILE *fp;
	unsigned long long int n, i;

	if (ac != 2)
	{
		printf("Usage: factors <file>\n");
		return (1);
	}

	fp = fopen(av[1], "r");
	if (fp == NULL)
	{
		printf("Error: Can't open file %s\n", av[1]);
		return (1);
	}


	while (fscanf(fp, "%lluULL", &n) != EOF)
	{
		for (i = 2; i <= sqrt(n); i++)
		{
			if (n % i == 0)
			{
				printf("%lu=%lu*%lu\n", n, n / i, i);
				break;
			}
		}
	}
	fclose(fp);
	return (0);
}
