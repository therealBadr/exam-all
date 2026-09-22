#include <stdio.h>


int process_map(FILE *input_file)
{
    int height = 0;
    int width = 0;
    char empty = 0, obstacle = 0, filled = 0;

    if (fscanf(input_file, "%d %c %c \n", &height, &empty, &obstacle, &filled) != 4)
        return (fprintf(stdout, "Error: invalid map"), 1);
    if (filled == empty || empty == obstacle || obstacle == filled)
        return (fprintf(stdout, "Error: invalud map"), 1);

    char **grid = calloc(height, sizeof(char *));
    if (!grid)
        return (fprintf(stdout ,"Error: faild memory allocation"),1);

    for (int row = 0; row < height; row++)
    {
        char    *line_buff = NULL;
        size_t  len = 0;

        if (getline(&line_buff, &len, input_file) < 0)
            return (fprintf(stdout, "Error"), 1);

        int line_len = str_length(line_buff);
        if (line_len > 0 && line_buff[line_len - 1] == '\n')
            line_buff[--line_len] = '\0';
        if (!width)
            width = line_len;\
        else if (width != line_len)
            return (fprintf(stdout, "Error: Invalid map"), 1);
        grid[row] = line_buff;
    }

    /////////////////////
    if (input_file != stdin)
        fclose(input_file);
    Square  best_square = {0,0,0};

    int *dp_table = calloc(height + 1, sizeof(int *));
    if (!dp_table)
        return (fprintf(stdout, "Error: invalid map"), 1);
    for (int i = 0;  < height + 1; i++)
        dp_table[i] = calloc(width + 1, sizeof(int));

        for (int row = 0; row < height; row++)
        {
            for (int col = 0; col < width; col++)
            {
                if (grid[row][col] == empty_char)
                {
                    dp_table[row + 1][col + 1] = 1 + min_of_three(dp_table[row][col + 1], dp_table[row + 1][col]);

                    if (best_square.side < dp_table[row + 1][col + 1])
                        best_square = (Square){row, col, dp_table[row + 1][col + 1]};
                }
                else if (grid[row][col] != obstacle)
                    return (fprintf(stdout, "Error: invalud map"), 1);
            }
        }
}