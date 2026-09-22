#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 4)
        return 1;

    int width = atoi(argv[1]);
    int height = atoi(argv[2]);
    int iterations = atoi(argv[3]);

    if (width <= 0 || height <= 0 || iterations < 0)
        return 1;

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

    int row = 1;
    int column = 1;
    int pen_down = 0;
    char command;

    while (read(0, &command, 1) > 0)
    {
        if (command == 'x')
            pen_down = !pen_down;

        if (command == 'w' && row > 1)
            row--;
        else if (command == 'a' && column > 1)
            column--;
        else if (command == 's' && row < height)
            row++;
        else if (command == 'd' && column < width)
            column++;

        if (pen_down)
            board[0][row][column] = 1;
    }

    for (int generation = 0; generation < iterations; generation++)
    {
        int current_board = generation % 2;
        int next_board = (generation + 1) % 2;

        for (int row = 1; row <= height; row++)
        {
            for (int column = 1; column <= width; column++)
            {
                int neighbors = 0;

                for (int row_offset = -1; row_offset <= 1; row_offset++)
                {
                    for (int column_offset = -1; column_offset <= 1; column_offset++)
                    {
                        if (row_offset != 0 || column_offset != 0)
                            neighbors += board[current_board]
                                [row + row_offset]
                                [column + column_offset];
                    }
                }

                if (neighbors == 3 ||
                    (neighbors == 2 && board[current_board][row][column]))
                    board[next_board][row][column] = 1;
                else
                    board[next_board][row][column] = 0;
            }
        }
    }

    int final_board = iterations % 2;

    for (int row = 1; row <= height; row++)
    {
        for (int column = 1; column <= width; column++)
        {
            if (board[final_board][row][column])
                putchar('O');
            else
                putchar(' ');
        }
        putchar('\n');
    }

    return 0;
}

// #include <stdlib.h>
// #include <unistd.h>
// #include <stdio.h>

// int main(int ac , char **av){
//     if(ac == 1)
//         return 1;
//     int widith = atoi(av[1]);
//     int hieght = atoi(av[2]);
//     int iterations = atoi(av[3]);
//     if(widith <= 0 || hieght <= 0 || iterations < 0)
//         return 1;
//     int grid[2][hieght +2][widith +2];
//     for(int i = 0; i < 2 ;i++)
//     {
//         for(int h =0 ; h < hieght +2 ;h++)
//         {
//             for(int w = 0; w <widith +2 ; w++)
//             {
//                 grid[i][h][w] = 0;
//             }
//         }
//     }
//     int x = 1 , y = 1 , pen = 0;
//     char cmd;
//     while (read(0 , &cmd ,1) > 0)
//     {
//         if(cmd == 'x')
//             pen = !pen;
//         if(cmd == 'w' && x > 1)
//             x--;
//         else if(cmd == 'a' && y > 1)
//             y--;
//         else if (cmd == 's' && x < hieght)
//             x++;
//         else if(cmd =='d' && y < widith)
//             y++;
//         if(pen)
//             grid[0][x][y] = 1;
//     }

//     for(int i = 0; i < iterations ; i++)
//     {
//         for(int h = 1; h < hieght +1 ; h++)
//             for(int w = 1 ;  w <widith +1 ;w++)
//             {    int nb =0;
//                 for(int x = -1 ; x <= 1 ; x++){
//                     for(int y =-1 ; y <= 1; y++)
//                     {
//                         if(x != 0 || y != 0)
//                             nb+=grid[i %2][h +x][y +w];
//                     }
//                 }
//                 if(((nb == 2 || nb == 3) && grid[i %2][h][w]) || nb ==3 )
//                     grid[(i +1) %2][h][w] = 1;
//                 else
//                     grid[(i +1) %2][h][w] = 0;;

//             }
//     }
//      for(int h = 1; h < hieght +1 ; h++){
//             for(int w = 1 ;  w <widith +1 ;w++){
//                 putchar(grid[iterations %2][h][w] ? 'O' :' ');
//             }
//         putchar('\n');
//      }   
// }