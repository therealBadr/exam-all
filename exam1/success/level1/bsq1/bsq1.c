#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

// ==========================================
// 1. STRUCTURES & HELPER FUNCTIONS
// ==========================================

/* Holds the tracking data for the largest valid square found */
typedef struct {
    int row;
    int col;
    int side;
} Square;

/* Calculates the length of a string manually */
int str_length(char *str) {
    int i = 0;
    while(str[i])
        i++;
    return i;
}

/* Returns the lowest value among three integers */
int min_of_three(int a, int b, int c) {
    int min = a;
    if(min > b)
        min = b;
    if(min > c)
        min = c;
    return min;
}

/* Frees the grid and the DP table (safe to call with NULL or partly filled tables) */
void free_all(char **grid, int **dp_table, int height) {
    if(grid) {
        for(int i = 0; i < height; i++)
            free(grid[i]);
        free(grid);
    }
    if(dp_table) {
        for(int i = 0; i < height + 1; i++)
            free(dp_table[i]);
        free(dp_table);
    }
}

/* Frees everything, prints the error, returns 1 */
int map_error(char **grid, int **dp_table, int height, char *line) {
    free(line);
    free_all(grid, dp_table, height);
    fprintf(stdout, "Error: invalid map\n");
    return 1;
}

// ==========================================
// 2. CORE MAP PROCESSING ENGINE
// ==========================================

int process_map(FILE *input_file) {
    int height = 0;
    int width = 0;
    char empty_char, obstacle_char, filled_char;
    char **grid = NULL;
    int **dp_table = NULL;
    char *line = NULL;
    size_t len = 0;
    ssize_t n;

    // --- Step A: Parse and Validate Header (e.g. "9015") ---
    n = getline(&line, &len, input_file);

    // Need at least 1 digit + 3 symbols + '\n'
    if(n < 5 || line[n - 1] != '\n')
        return map_error(NULL, NULL, 0, line);

    empty_char    = line[n - 4];
    obstacle_char = line[n - 3];
    filled_char   = line[n - 2];

    // Everything before the 3 symbols is the number (manual atoi)
    for(int i = 0; i < n - 4; i++) {
        if(line[i] < '0' || line[i] > '9' || height > 100000000)
            return map_error(NULL, NULL, 0, line);
        height = height * 10 + (line[i] - '0');
    }

    if(height <= 0)
        return map_error(NULL, NULL, 0, line);

    if(filled_char == empty_char || empty_char == obstacle_char || obstacle_char == filled_char)
        return map_error(NULL, NULL, 0, line);

    // --- Step B: Allocate Memory for Grid ---
    grid = calloc(height, sizeof(char *));
    if(!grid)
        return map_error(NULL, NULL, 0, line);

    // --- Step C: Read Grid Lines, Validate Widths and Characters ---
    for(int row = 0; row < height; row++) {
        n = getline(&line, &len, input_file);
        if(n <= 0)
            return map_error(grid, NULL, height, line);

        // Strip trailing newline character
        if(line[n - 1] == '\n')
            line[--n] = '\0';

        // Empty lines are not allowed
        if(n == 0)
            return map_error(grid, NULL, height, line);

        // Establish or check width consistency
        if(row == 0)
            width = n;
        else if(width != n)
            return map_error(grid, NULL, height, line);

        // Only empty and obstacle characters are allowed
        for(int col = 0; col < width; col++)
            if(line[col] != empty_char && line[col] != obstacle_char)
                return map_error(grid, NULL, height, line);

        // The grid keeps this buffer; getline will allocate a new one
        grid[row] = line;
        line = NULL;
        len = 0;
    }

    // --- Step D: Reject Extra Lines After the Declared Height ---
    if(getline(&line, &len, input_file) > 0)
        return map_error(grid, NULL, height, line);
    free(line);
    line = NULL;

    // --- Step E: Allocate Dynamic Programming (DP) Table ---
    dp_table = calloc(height + 1, sizeof(int *));
    if(!dp_table)
        return map_error(grid, NULL, height, NULL);

    for(int i = 0; i < height + 1; i++) {
        dp_table[i] = calloc(width + 1, sizeof(int));
        if(!dp_table[i])
            return map_error(grid, dp_table, height, NULL);
    }

    // --- Step F: Solve BSQ Using Dynamic Programming ---
    Square best_square = {0, 0, 0};
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
            if(grid[row][col] == empty_char) {
                // DP Rule: 1 + min of (top, left, top-left)
                dp_table[row + 1][col + 1] = 1 + min_of_three(
                    dp_table[row][col + 1],
                    dp_table[row + 1][col],
                    dp_table[row][col]
                );

                // Track the largest square seen so far
                if(best_square.side < dp_table[row + 1][col + 1])
                    best_square = (Square){row, col, dp_table[row + 1][col + 1]};
            }
        }
    }

    // --- Step G: Draw the Largest Square on the Grid ---
    for(int r = best_square.row - best_square.side + 1; r <= best_square.row; r++) {
        for(int c = best_square.col - best_square.side + 1; c <= best_square.col; c++) {
            grid[r][c] = filled_char;
        }
    }

    // --- Step H: Output the Final Visualized Grid ---
    for(int row = 0; row < height; row++) {
        fprintf(stdout, "%s\n", grid[row]);
    }

    free_all(grid, dp_table, height);
    return 0;
}

// ==========================================
// 3. FILE LOADING & DRIVER (MAIN)
// ==========================================

/* Opens a file, processes it, and always closes it */
void process_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file) {
        fprintf(stdout, "Error: invalid map\n");
        return;
    }
    process_map(file);
    fclose(file);
}

/* Program entry point: stdin if no arguments, otherwise each file in order */
int main(int argc, char **argv) {
    if(argc == 1) {
        process_map(stdin);
    }
    else {
        for(int i = 1; i < argc; i++) {
            process_file(argv[i]);
            // Blank separation line between maps
            if(i < argc - 1)
                fprintf(stdout, "\n");
        }
    }
    return 0;
}

// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>

// // ==========================================
// // 1. STRUCTURES & HELPER FUNCTIONS
// // ==========================================

// /* Holds the tracking data for the largest valid square found */
// typedef struct {
//     int row;
//     int col;
//     int side;
// } Square;

// /* Calculates the length of a string manually */
// int str_length(char *str) {
//     int i = 0;
//     while(str[i])
//         i++;
//     return i;
// }

// /* Returns the lowest value among three integers */
// int min_of_three(int a, int b, int c) {
//     int min = a;
//     if(min > b)
//         min = b;
//     if(min > c)
//         min = c;
//     return min;
// } 


// // ==========================================
// // 2. CORE MAP PROCESSING ENGINE
// // ==========================================

// int process_map(FILE *input_file) 

// {
//     int height = 0;
//     char empty_char = 0, obstacle_char = 0, filled_char = 0;

//     // --- Step A: Parse and Validate Header ---
//     char *line_zayb = NULL;
//     size_t len = 0;
//     ssize_t n = getline(&line_zayb, &len, input_file);

//     // Need at least 1 digit + 3 symbols + '\n'
//     if(n < 5 || line_zayb[n - 1] != '\n')
//         return (free(line_zayb), fprintf(stdout, "Error: invalid map1\n"), 1);

//     empty_char    = line_zayb[n - 4];
//     obstacle_char = line_zayb[n - 3];
//     filled_char   = line_zayb[n - 2];

//     // Everything before the 3 symbols is the number
//     for(int i = 0; i < n - 4; i++) {
//         if(line_zayb[i] < '0' || line_zayb[i] > '9')
//             return (free(line_zayb), fprintf(stdout, "Error: invalid map1\n"), 1);
//         height = height * 10 + (line_zayb[i] - '0');
//         printf("%d\n",height);
//     }
//     free(line_zayb);

//     if(height <= 0)
//         return (fprintf(stdout, "Error: invalid map1\n"), 1);

//     if(filled_char == empty_char || empty_char == obstacle_char || obstacle_char == filled_char)
//         return (fprintf(stdout, "Error: invalid map2\n"), 1);
        

//     // --- Step B: Allocate Memory for Grid ---
//     char **grid = calloc(height, sizeof(char *));
//     if(!grid)
//         return (fprintf(stdout, "Error: faild memory allocation"), 1);
        
//     int width = 0;

//     // --- Step C: Read Grid Lines & Validate Widths ---
//     for(int row = 0; row < height; row++) {
//         char *line_buf = NULL;
//         size_t len = 0;
        
//         if(getline(&line_buf, &len, input_file) < 0)
//             return (fprintf(stdout, "Error"), 1);
            
//         int line_len = str_length(line_buf);
        
//         // Strip trailing newline character
//         if(line_len > 0 && line_buf[line_len - 1] == '\n')
//             line_buf[--line_len] = '\0';
            
//         // Establish or check width consistency
//         if(!width)
//             width = line_len;
//         else if(width != line_len)
//             return (fprintf(stdout, "Error: invalid map3"), 1);
            
//         grid[row] = line_buf;
//     }

//     // --- Step D: Clean Up File Stream ---
//     if(input_file != stdin)
//         fclose(input_file);

//     // --- Step E: Allocate Dynamic Programming (DP) Table ---
//     Square best_square = {0, 0, 0};
//     int **dp_table = calloc(height + 1, sizeof(int*));
//     if(!dp_table)
//         return (fprintf(stdout, "Error: invalid map4"), 1);

//     for(int i = 0; i < height + 1; i++)
//         dp_table[i] = calloc(width + 1, sizeof(int));

//     // --- Step F: Solve BSQ Using Dynamic Programming ---
//     for(int row = 0; row < height; row++) {
//         for(int col = 0; col < width; col++) {
//             if(grid[row][col] == empty_char) {
//                 // DP Rule: 1 + min of (top, left, top-left)
//                 dp_table[row + 1][col + 1] = 1 + min_of_three(
//                     dp_table[row][col + 1], 
//                     dp_table[row + 1][col], 
//                     dp_table[row][col]
//                 );
                
//                 // Track the largest square seen so far
//                 if(best_square.side < dp_table[row + 1][col + 1])
//                     best_square = (Square){row, col, dp_table[row + 1][col + 1]};
//             }
//             else if(grid[row][col] != obstacle_char) {
//                 return (fprintf(stdout, "Error: invalid map5"), 1);
//             }
//         }
//     }

//     // --- Step G: Draw the Largest Square on the Grid ---
//     for(int r = best_square.row - best_square.side + 1; r <= best_square.row; r++) {
//         for(int c = best_square.col - best_square.side + 1; c <= best_square.col; c++) {
//             grid[r][c] = filled_char;
//         }
//     }

//     // --- Step H: Output the Final Visualized Grid ---
//     for(int row = 0; row < height; row++) {
//         fprintf(stdout, "%s\n", grid[row]);
//     }
    
//     return 0;
// }

// // ==========================================
// // 3. FILE LOADING & DRIVER (MAIN)
// // ==========================================

// /* Safely opens a file path and passes it to the map engine */
// void process_file(char *filename) 
// {
//     FILE *file = fopen(filename, "r");
//     if(!file)
//         return;
//     process_map(file);
// }

// /* Program entry point handling routing for stdin or multiple files */
// int main(int argc, char **argv) {
//     if(argc == 1) {
//         process_map(stdin);
//     }
//     else if(argc >= 2) {
//         for(int i = 1; i < argc; i++) {
//             process_file(argv[i]);
//             // Output blank separation line between maps
//             if(i < argc - 1)
//                 fprintf(stdout, "\n");
//         }
//     }
//     else {
//         printf("ERROR : too many argument\n");
//     }
    
//     return 0;
// }

