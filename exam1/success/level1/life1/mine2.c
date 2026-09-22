#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int	main(int ac, char **av)
{
	if (ac != 4)
		return 1;
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iterations = atoi(av[3]);
	if (widht <= 0 || height <= 0 || iterations < 0
		return 1;
	int board[2][height + 2][width + 2];

	for (int board_index = 0; board_index < 2; board_index++)
	return 0;
}
