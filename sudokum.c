#include <stdio.h>
#include <stdbool.h>

#define N 9

void print_board(int board[N][N]) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            printf("%d ", board[i][j]);
        }
        printf("\n");
    }
}

bool find_empty_location(int board[N][N], int *row, int *col) {
    for (*row = 0; *row < N; (*row)++) {
        for (*col = 0; *col < N; (*col)++) {
            if (board[*row][*col] == 0) {
                return true;
            }
        }
    }
    return false;
}

bool is_safe(int board[N][N], int row, int col, int num) {
    // Check if 'num' is not in the current row
    for (int i = 0; i < N; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }

    // Check if 'num' is not in the current column
    for (int i = 0; i < N; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }

    // Check if 'num' is not in the current 3x3 box
    int start_row = row - row % 3;
    int start_col = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + start_row][j + start_col] == num) {
                return false;
            }
        }
    }

    return true;
}

bool solve_sudoku(int board[N][N]) {
    int row, col;
    if (!find_empty_location(board, &row, &col)) {
        return true; // Puzzle solved
    }

    for (int num = 1; num <= 9; num++) {
        if (is_safe(board, row, col, num)) {
            board[row][col] = num;

            if (solve_sudoku(board)) {
                return true;
            }

            // Backtrack
            board[row][col] = 0;
        }
    }
    return false;
}

int main() {
    int sudoku_board[N][N] = {
        {5, 3, 0, 0, 7, 0, 0, 0, 0},
        {6, 0, 0, 1, 9, 5, 0, 0, 0},
        {0, 9, 8, 0, 0, 0, 0, 6, 0},
        {8, 0, 0, 0, 6, 0, 0, 0, 3},
        {4, 0, 0, 8, 0, 3, 0, 0, 1},
        {7, 0, 0, 0, 2, 0, 0, 0, 6},
        {0, 6, 0, 0, 0, 0, 2, 8, 0},
        {0, 0, 0, 4, 1, 9, 0, 0, 5},
        {0, 0, 0, 0, 8, 0, 0, 7, 9}
    };

    if (solve_sudoku(sudoku_board)) {
        printf("Sudoku puzzle solved successfully!\n");
        print_board(sudoku_board);
    } else {
        printf("No solution exists for the given Sudoku puzzle.\n");
    }

    return 0;
}
