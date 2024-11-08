#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define N 9

// Function to check if a number can be placed in a cell
bool isSafe(int grid[N][N], int row, int col, int num) {
    for (int x = 0; x < N; x++) {
        if (grid[row][x] == num || grid[x][col] == num)
            return false;
    }

    int startRow = row - row % 3, startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (grid[i + startRow][j + startCol] == num)
                return false;
        }
    }
    return true;
}

// Backtracking function to fill the grid
bool fillGrid(int grid[N][N]) {
    int row = -1, col = -1;
    bool isEmpty = false;

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (grid[i][j] == 0) {
                row = i;
                col = j;
                isEmpty = true;
                break;
            }
        }
        if (isEmpty) break;
    }

    if (!isEmpty) return true;

    for (int num = 1; num <= 9; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num;
            if (fillGrid(grid))
                return true;
            grid[row][col] = 0;
        }
    }
    return false;
}

// Function to remove random numbers to create a puzzle
void removeRandomCells(int grid[N][N]) {
    int cellsToRemove = 30 + rand() % 21; // Randomly remove between 30 to 50 cells
    while (cellsToRemove != 0) {
        int cellId = rand() % 81;
        int row = cellId / 9;
        int col = cellId % 9;
        if (grid[row][col] != 0) {
            grid[row][col] = 0;
            cellsToRemove--;
        }
    }
}

// Function to generate a Sudoku puzzle
void generateSudoku(int grid[N][N]) {
    // Initialize the grid with 0
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            grid[i][j] = 0;
        }
    }

    // Seed the random generator
    srand(time(0));

    // Fill the diagonal boxes (3x3 sub-grids)
    for (int i = 0; i < N; i += 3) {
        for (int j = 1; j <= 9; j++) {
            int row = i + rand() % 3;
            int col = i + rand() % 3;
            while (grid[row][col] != 0) {
                row = i + rand() % 3;
                col = i + rand() % 3;
            }
            grid[row][col] = j;
        }
    }

    // Complete the grid with backtracking
    fillGrid(grid);

    // Remove random cells to create the puzzle
    removeRandomCells(grid);
}

// Function to print the grid
void printGrid(int grid[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%2d", grid[i][j]);
        }
        printf("\n");
    }
}

int main() {
    int grid[N][N];
    
    generateSudoku(grid);
    
    printGrid(grid);
    
    return 0;
}
