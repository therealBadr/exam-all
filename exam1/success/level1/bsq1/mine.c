#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	process_map(FILE *input_file)
{
	int	height = 0;
	char	empty = 0, obstacle = 0, filled = 0;
	// 1- vlidate the header
	// change spaces later to expect no spaces format
	if (fscanf(input_file, "%d %c %c %c", &height, &empty, &obstacle, &filled) != 4)
	{
		if (input_file != stdin)
			fclose(input_file);
		return (fprintf(stdout, "Error: invalid map\n",), 1);
	}
	// 2- Move to the next line: consume everything until nl
	int c;

	while ((c = fgetc(input_line)) != '\n' && c != EOF)
		;
	if (height <= 0 || filled == empty || empty == obstacle || filled == obstacle)
	{
		if (input_file != stdin)
			fclose(input_file);
		return (fprintf(stdout, "Error: invalid map\n"), 1);
	}

	// 3- Allocate the map
	char	**grid = calloc(height, sizeof(char *));
	if (!grid)
		return (fprintf(stdout, "Error: failed memory allocation\n"), 1);
	int width = 0;

	// 4- read, validate each map row. Store rows into grid[]
	for (int row = 0; row < height; row++)
	{
		char	*line_buff = NULL;
		size_t	len = 0;

		
		// read the line
		if (getline(&line_buff, &len, input_file) < 0)
		{
			free(line_buff);
			free_grid(grid, row);
			if (input_file != stdin)
				fclose(input_file);
			return (fprintf(stdout, "Error: invalid map\n"), 1);
		}
		// 
		int	line_len = ft_strlen(line_buff);
		if (line_len > 0 && line_buff[line_len - 1] == '\n')
			line_buff[--line_len] = '\0';
		if (line_len == 0)
		{
			free(line_buff);
			free_grid(grid, row);
			if (input_file != stdin)
				fclose(input_file);
			return (fprintf(stdout, "Error: invalid map\n", 1);
		}
		if (!width)
			width = line_len;
		else if (width != line_len)
		{
			free(line_buf);
			free_grid(grid, row);
			if (input_file != stdin)
			return fprintf(stdout, "Error: invalid map\n", 1);
		}
		grid[row] = line_buff;
	}
	if (input_file != stdin)
		fclose(input_file);
	
}

void	process_file(char *filename)
{
	FILE	*file = fopen(filename, "r");
	if (!file)
		return (void)fprintf(stdout, "Error: %s: cannot open file\n", filename);
	process_map(file);
}

int	main(int ac, char **av)
{
	if (ac == 1)
		process_map(stdin);
	else if (ac == 2)
		process_file(av[1]);
	else
		fprintf(stdout, "Error: too many arguments\n");
	return 0;
}
