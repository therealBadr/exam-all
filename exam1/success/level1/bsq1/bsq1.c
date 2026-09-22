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

// ==========================================
// 2. CORE MAP PROCESSING ENGINE
// ==========================================

int process_map(FILE *input_file) {
    int height = 0;
    char empty_char = 0, obstacle_char = 0, filled_char = 0;

    // --- Step A: Parse and Validate Header ---
    if(fscanf(input_file, "%d %c %c %c \n", &height, &empty_char, &obstacle_char, &filled_char) != 4)
        return (fprintf(stdout, "Error: invalid map"), 1);
        
    if(filled_char == empty_char || empty_char == obstacle_char || obstacle_char == filled_char)
        return (fprintf(stdout, "Error: invalid map"), 1);

    // --- Step B: Allocate Memory for Grid ---
    char **grid = calloc(height, sizeof(char *));
    if(!grid)
        return (fprintf(stdout, "Error: faild memory allocation"), 1);
        
    int width = 0;

    // --- Step C: Read Grid Lines & Validate Widths ---
    for(int row = 0; row < height; row++) {
        char *line_buf = NULL;
        size_t len = 0;
        
        if(getline(&line_buf, &len, input_file) < 0)
            return (fprintf(stdout, "Error"), 1);
            
        int line_len = str_length(line_buf);
        
        // Strip trailing newline character
        if(line_len > 0 && line_buf[line_len - 1] == '\n')
            line_buf[--line_len] = '\0';
            
        // Establish or check width consistency
        if(!width)
            width = line_len;
        else if(width != line_len)
            return (fprintf(stdout, "Error: invalid map"), 1);
            
        grid[row] = line_buf;
    }

    // --- Step D: Clean Up File Stream ---
    if(input_file != stdin)
        fclose(input_file);

    // --- Step E: Allocate Dynamic Programming (DP) Table ---
    Square best_square = {0, 0, 0};
    int **dp_table = calloc(height + 1, sizeof(int*));
    if(!dp_table)
        return (fprintf(stdout, "Error: invalid map"), 1);

    for(int i = 0; i < height + 1; i++)
        dp_table[i] = calloc(width + 1, sizeof(int));

    // --- Step F: Solve BSQ Using Dynamic Programming ---
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
            else if(grid[row][col] != obstacle_char) {
                return (fprintf(stdout, "Error: invalid map"), 1);
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
    
    return 0;
}

// ==========================================
// 3. FILE LOADING & DRIVER (MAIN)
// ==========================================

/* Safely opens a file path and passes it to the map engine */
void process_file(char *filename) {
    FILE *file = fopen(filename, "r");
    if(!file)
        return;
    process_map(file);
}

/* Program entry point handling routing for stdin or multiple files */
int main(int argc, char **argv) {
    if(argc == 1) {
        process_map(stdin);
    }
    else if(argc >= 2) {
        for(int i = 1; i < argc; i++) {
            process_file(argv[i]);
            // Output blank separation line between maps
            if(i < argc - 1)
                fprintf(stdout, "\n");
        }
    }
    else {
        printf("ERROR : too many argument\n");
    }
    
    return 0;
}


// #include <unistd.h>
// #include <stdlib.h>
// #include <stdio.h>

// typedef struct {int row, col, side;} Square;

// int str_length(char *str){
//     int i = 0;
//     while(str[i])
//         i++;
//     return i;
// }

// int min_of_three(int a , int b ,int c)
// {
//     int min = a;
//     if(min > b)
//         min = b;
//     if(min > c)
//         min = c;
//     return min;
// }

// int process_map(FILE *input_file)
// {
//     int height = 0;
//     char empty_char = 0 , obstacle_char = 0 , filled_char = 0;
//     if(fscanf(input_file ,"%d %c %c %c \n",&height ,&empty_char ,&obstacle_char ,&filled_char) != 4)
//         return (fprintf(stdout ,"Error: invalid map"),1);
//     if(filled_char == empty_char || empty_char == obstacle_char || obstacle_char == filled_char)
//         return (fprintf(stdout ,"Error: invalid map"),1);
//     char **grid = calloc(height ,sizeof(char *));
//     if(!grid)
//         return (fprintf(stdout ,"Error: faild memory allocation"),1);
//     int width = 0;

//     for(int row = 0 ; row < height ; row++)
//     {
//         char *line_buf = NULL;
//         size_t len = 0;
//         if(getline(&line_buf , &len , input_file) < 0)
//             return (fprintf(stdout ,"Error"),1);
//         int line_len = str_length(line_buf);
//         if(line_len > 0 && line_buf[line_len - 1] == '\n')
//             line_buf[--line_len] = '\0';
//         if(!width)
//             width = line_len;
//         else if(width != line_len)
//                 return (fprintf(stdout ,"Error: invalid map"),1);
//         grid[row] = line_buf;
//     }

//     if(input_file != stdin)
//         fclose(input_file);
//     Square best_square = {0,0,0};
//     int **dp_table = calloc(height +1 , sizeof(int*));
//     if(!dp_table)
//         return (fprintf(stdout ,"Error: invalid map"),1);

//     for(int i = 0 ; i < height +1 ; i++)
//         dp_table[i] = calloc(width +1 ,sizeof(int));

//     for(int row = 0; row < height ;row++){
//         for(int col = 0; col < width ; col++)
//         {
//             if(grid[row][col] == empty_char)
//             {
//                 dp_table[row +1][col +1] = 1 + min_of_three(dp_table[row][col +1] ,dp_table[row+1][col] ,dp_table[row][col]);
//                 if(best_square.side < dp_table[row +1][col +1])
//                     best_square = (Square){row , col, dp_table[row+1][col +1]};
//             }
//                 else if(grid[row][col] != obstacle_char)
//                      return (fprintf(stdout ,"Error: invalid map"),1);
//         }
//     }

//     for(int r = best_square.row - best_square.side +1 ; r <= best_square.row ; r++)
//     {
//         for(int c = best_square.col - best_square.side +1 ; c <= best_square.col ; c++)
//         {
//             grid[r][c] = filled_char;
//         }
//     }


//     for(int row = 0 ; row < height ; row++)
//     {
//         fprintf(stdout , "%s\n",grid[row]);
//     }
//     return 0;
// }
// void process_file(char *filename)
// {
//     FILE *file = fopen(filename , "r");
//     if(!file)
//         return ;
//     process_map(file);
// }
// int main(int argc , char **argv)
// {
//     if(argc == 1)
//         process_map(stdin);
//     else if(argc >= 2){
//         for(int i = 1 ; i < argc ; i++)
//         {
//             process_file(argv[i]);
//             if(i < argc -1)
//                 fprintf(stdout , "\n");
//         }
//     }
//     else 
//         printf("ERROR : too many argument\n");
//     return 0;
// }