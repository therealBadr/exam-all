#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct 
{
	int row;
	int col;
	int sid;
} Square;


int	process_map(FILE *input_file)
{
	int height = 0;
	char empty = 0, obstacle = 0, filled =0;
	char *header = NULL;
	size_t header_len = 0;
	size_t header_size = getline(&header, &header_len, input_file);
	if (header_size < 5)
		return (fprintf(stdout, "Error: invalid map"), 1);
	empty = header[header_len - 4];
	obstacle = header[header_len - 3];
	filled = header[header_len - 2];

	for (int i = 0; i < 4; i++)
	{
		if (header[i] < '0' || header[i] > '9')
			return (fprintf(stdout, "Error"), 1);
		height = height * 10 + (header[i] - '0');
	}

	if (height <= 0 || empty == obstacle || empty == filled || obstacle == filled)
		return //error

	char **grid 
}

void	process_file(char *filename)
{
	FILE *file = fopen(filename, "r");
	if (!file)
		return;
	process_map(file);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		process_map(stdin);
	else if (ac >= 2)
	{
		for (int i = 1; i < ac; i++)
		{
			process_file(av[i]);
			if (i < ac - 1)
				fprintf(stdout, "\n");
		}			
	}
	else
		printf("ERROR: too mant args\n");
	return 0;
}