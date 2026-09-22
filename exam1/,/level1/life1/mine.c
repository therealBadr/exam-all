#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#define ERROR 1

int	main(int ac, char **av)
{
	// =============================================
	// check if ac == 1, then fail
	if (ac == 1) // maybe we check for ac == 3 too
		return ERROR;
	// collect data here, 3 args 
	int width = atoi(av[1]);
	int height = atoi(av[2]);
	int iterations = atoi(av[3]);


	// check data collected
	if (width <= 0 || height <= 0 || iterations < 0)
		return ERROR;
	// =============================================


	// =============================================
	// 1- create and fill the board 
	int board[2][height + 2][width + 2];
	for (int board_index = 0; board_index < 2; board_index++)
	{
		for (int row = 0; row < height + 2; row++)
		{
			for (int column = 0; column < width + 2; column++)
			{
				board[board_index][row][column] = 0;
			}
		}		
	}
	
	int row = 1; int column = 1;
	int pen_flag = 0;
	char cmd;

	while (read(0, &cmd, 1) > 0)
	{
		if (cmd == 'x')
			pen_flag = !pen_flag;
		if (cmd == 'w' && row > 1)
			row--;
		else if (cmd == 's' && row < height)
			row++;
		else if (cmd == 'd' && column < width)
			column++;
		else if (cmd == 'a' && column > 1)
			column--;
		if (pen_flag)
			board[0][row][column] = 1;
	}

	// =============================================

	for (int gen = 0; gen < iterations; gen++)
	{
		int curr = gen % 2;
		int next = (gen + 1) % 2;
		for (int row = 1; row <= height; row++)
		{
			for (int col = 1; col <= width; col++)
			{
				int neighbours = 0;
				for (int row_offset = -1; row_offset <= 1; row_offset++)
				{
					for (int col_offset = -1; col_offset <= 1; col_offset++)
					{
						if (row_offset != 0 || col_offset != 0)
							neighbours += board[curr][row + row_offset][col + col_offset];
					}
				}
				if (neighbours == 3 || (neighbours == 2 && board[curr][row][col]))
					board[next][row][col] = 1;
				else
					board[next][row][col] = 0;
			}
		}
	}

	int final_board = iterations % 2;
	for (int row = 1; row <= height; row++)
	{
		for (int col = 1; col <= width; col++)
		{
			if (board[final_board][row][col])
				putchar('O');
			else
				putchar(' ');
		}
		putchar('\n');
	}

	return 0;
}