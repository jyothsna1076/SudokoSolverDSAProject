#include <iostream>
#include <vector>
#include <unordered_map>
#include <set>
#include <utility>

#define N 9
using namespace std;

// Hash maps for rows, columns, and boxes (used in MRV + Hash)
unordered_map<int, set<int>> rowMap, colMap, boxMap;
 vector<vector<set<int>>> options(N, vector<set<int>>(N));
 // To store possible values for each cell

// Calculate box index for MRV+Hash method
int getBoxIndex(int row, int col) {
    return (row / 3) * 3 + col / 3;
}

// Initialize hash maps and options for MRV+Hash
void initializeOptions(vector<vector<int>>& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    int boxIndex = getBoxIndex(row, col);
                    if (rowMap[row].find(num) == rowMap[row].end() &&
                        colMap[col].find(num) == colMap[col].end() &&
                        boxMap[boxIndex].find(num) == boxMap[boxIndex].end()) {
                        options[row][col].insert(num);
                    }
                }
            }
        }
    }
}

// Place a number in MRV+Hash
void placeNumber(vector<vector<int>>& board, int row, int col, int num) {
    int boxIndex = getBoxIndex(row, col);
    rowMap[row].insert(num);
    colMap[col].insert(num);
    boxMap[boxIndex].insert(num);
    board[row][col] = num;

    for (int i = 0; i < N; i++) {
        options[row][i].erase(num);
        options[i][col].erase(num);
        options[(row / 3) * 3 + i / 3][(col / 3) * 3 + i % 3].erase(num);
    }
}

// Remove number in MRV+Hash
void removeNumber(vector<vector<int>>& board, int row, int col, int num) {
    int boxIndex = getBoxIndex(row, col);
    rowMap[row].erase(num);
    colMap[col].erase(num);
    boxMap[boxIndex].erase(num);
    board[row][col] = 0;

    for (int i = 0; i < N; i++) {
        if (board[row][i] == 0) options[row][i].insert(num);
        if (board[i][col] == 0) options[i][col].insert(num);
        int boxRow = (row / 3) * 3 + i / 3;
        int boxCol = (col / 3) * 3 + i % 3;
        if (board[boxRow][boxCol] == 0) options[boxRow][boxCol].insert(num);
    }
}

// Check validity using hash maps
bool isValid(int row, int col, int num) {
    int boxIndex = getBoxIndex(row, col);
    return rowMap[row].find(num) == rowMap[row].end() &&
           colMap[col].find(num) == colMap[col].end() &&
           boxMap[boxIndex].find(num) == boxMap[boxIndex].end();
}

// MRV method to get cell with fewest options
pair<int, int> getMRVCell() {
    int minOptions = 10;
    pair<int, int> minCell = {-1, -1};

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (options[row][col].size() > 0 && options[row][col].size() < minOptions) {
                minOptions = options[row][col].size();
                minCell = {row, col};
            }
        }
    }
    return minCell;
}

// Solve Sudoku using MRV+Hash
bool solveMRV(vector<vector<int>>& board) {
    pair<int, int> cell = getMRVCell();
    if (cell.first == -1) return true;

    int row = cell.first, col = cell.second;

    for (int num : options[row][col]) {
        placeNumber(board, row, col, num);
        if (solveMRV(board)) return true;
        removeNumber(board, row, col, num);
    }
    return false;
}

// Simple Backtracking solve function
bool solveBacktracking(vector<vector<int>>& board) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (isValid(row, col, num)) {
                        board[row][col] = num;
                        if (solveBacktracking(board)) return true;
                        board[row][col] = 0;
                    }
                }
                return false;
            }
        }
    }
    return true;
}

// Print the board
void printBoard(const vector<vector<int>>& board) {
    for (const auto& row : board) {
        for (int num : row) {
            cout << num << " ";
        }
        cout << endl;
    }
}

// Main function
int main() {
    cout << "Enter elements of the Sudoku (row col num), -1 to finish:" << endl;
    vector<vector<int>> board(N, vector<int>(N, 0));

    int a = 1, row, col, element;
    while (a != -1) {
        cout << "Enter row, col, element:" << endl;
        cin >> row >> col >> element;
        board[row][col] = element;
        cout << "Another element? (1 for yes, -1 for no):" << endl;
        cin >> a;
    }

    cout << "Choose method:\n1. Backtracking\n2. MRV+Hash\n";
    int choice;
    cin >> choice;

    if (choice == 1) {
        cout << "Solving using Backtracking..." << endl;
        if (solveBacktracking(board)) {
            printBoard(board);
        } else {
            cout << "No solution exists." << endl;
        }
    } else if (choice == 2) {
        cout << "Solving using MRV+Hash..." << endl;
        initializeOptions(board);
        if (solveMRV(board)) {
            printBoard(board);
        } else {
            cout << "No solution exists." << endl;
        }
    } else {
        cout << "Invalid choice." << endl;
    }

    return 0;
}
