#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FILEPATH_LEN 256
#define GRID_COLROW_LEN 9

/* 2D indexing formula */
#define GI(row, col) ((GRID_COLROW_LEN*col) + row)

typedef unsigned char byte;

char filePath[MAX_FILEPATH_LEN];
byte grid[GRID_COLROW_LEN*GRID_COLROW_LEN];

void GetFileName()
{
    printf("Please input a .sudoku file to solve(Max path length = %i): ", MAX_FILEPATH_LEN);
    scanf("%s", filePath);
}

void PrintGrid()
{
    for (int c = 0; c < GRID_COLROW_LEN; c++)
    {
        printf("%i : ", c);
        for (int r = 0; r < GRID_COLROW_LEN; r++)
        {
            printf("%i ", grid[GI(r,c)]);
        }
        printf("\n");
    }
}

void Solve();

int main(int argc, char** argv)
{
    if (argc > 2)
        strcpy(filePath, argv[1]);
    else
        GetFileName();

    FILE* fpIn = fopen(filePath, "r");
    if (!fpIn)
    {
        fprintf(stderr, "Failed to read file!\n");
        return 1;
    }

    /* Read from file into grid */
    for (int c = 0; c < GRID_COLROW_LEN; c++)
    {
        for (int r = 0; r < GRID_COLROW_LEN; r++)
        {
            /* -48 is for converting from ascii to integer */
            grid[GI(r,c)] = fgetc(fpIn) - 48;
            fgetc(fpIn); // increment to avoid spaces
        }
    }
    fclose(fpIn);

    /* Run the algorithm */
    Solve();

    PrintGrid();

    return 0;
}

/* Check if number n is legal at index */
int Possible(int x, int y, int n)
{
    // Row check
    for (int i = 0; i < GRID_COLROW_LEN; i++)
    {
        if (grid[GI(i,y)] == n)
            return 0;
    }
    
    // Column check
    for (int i = 0; i < GRID_COLROW_LEN; i++)
    {
        if (grid[GI(x, i)] == n)
            return 0;
    }

    // Square check
    int squareX = x/3;
    int squareY = y/3;

    for (int ly = 0; ly < 3; ly++)
    {
        for (int lx = 0; lx < 3; lx++)
        {
            if (grid[(((squareY*3) + ly)*GRID_COLROW_LEN) + (squareX*3) + lx] == n)
                return 0;
        }
    }

    return 1;
}

/* Check if the grid has any 0's in it; if it is finished */
int IsFinished()
{
    for (int y = GRID_COLROW_LEN-1; y >= 0; y--)
        for(int x = GRID_COLROW_LEN-1; x >= 0; x--)
            if (grid[GI(x,y)] == 0) return 0;

    return 1;
}

/* Where the magic happens */
void Solve()
{
    for (int y = 0; y < GRID_COLROW_LEN; y++)
    {
        for(int x = 0; x < GRID_COLROW_LEN; x++)
        {
            if (grid[GI(x,y)] == 0)
            {
                for (int n = 1; n < 10; n++)
                {
                    if (Possible(x,y,n))
                    {
                        grid[GI(x,y)] = n;
                        Solve();
                        if(!IsFinished()) grid[GI(x,y)] = 0;
                    }
                }
                return;
            }
        }
    }
}