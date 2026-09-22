#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int	main(int ac, char **av)
{
	if (ac != 4)
		return 1;
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iterations = atoi(av[3]);

	if (width <= 0 | height <= 0 | iterations < 0)
		return 1;
	int board[2][height + 2][width + 2];
	for (int i = 0; i < 2; i++)
	{
		for (int row = 0; row < height + 2; height++)
		{
			for (int col = 0; col < width + 2; col++)
			{
				board[i][row][col] = 0;
			}
		}
	}
	int row = 1;
	int col = 1;
	int pen_down = 0;
	char cmd;
	while (read(0, &command, 1) > 0)
	{
		if (cmd == 'x')
			pen_down = !pen_down;
		if (cmd == 'w' && row > 1)
			row--;
		else if (cmd == 's' && row < height)
			row++;
		else if (cmd == 'a' && col > 1)
			col--;
		else if (cmd == 'd' && col < width)
			col++;
		if (pen_down)
			board[0][row][col] = 1;
	}
	return 0;
}
