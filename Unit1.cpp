#include <vcl.h>
#include <vector>
#include <unordered_set>
#include <string>
#include <fstream>
#include <iostream>
#include<queue>
#include <unordered_map>
#include <set>
#include <utility>
#include <random>
#pragma hdrstop
#include "Unit1.h"
#include "Unit2.h"
#include "Unit3.h"
#pragma package(smart_init)
#pragma resource "*.dfm"
#define N 9
using namespace std;
//vector<vector<set<int>>> options(N, vector<set<int>>(N));
TForm1 *Form1;

__fastcall TForm1::TForm1(TComponent* Owner) : TForm(Owner)
{
	StringGrid1->RowCount = 9;
	StringGrid1->ColCount = 9;
	for (int i = 0; i < 9; i++)
	{
		StringGrid1->ColWidths[i] = 40;
		StringGrid1->RowHeights[i] = 40;
	}
	StringGrid1->OnKeyDown = StringGrid1KeyDown;
}





void generateRandomSudoku(std::vector<std::vector<int>>& sudoku, 
                           std::vector<std::unordered_set<int>>& rows,
                           std::vector<std::unordered_set<int>>& cols,
                           std::vector<std::unordered_set<int>>& boxes)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(1, 9);

    // Helper function to check if placing a number is valid
    auto isValid = [&](int row, int col, int num) -> bool {
        int boxIndex = (row / 3) * 3 + (col / 3);
        return rows[row].find(num) == rows[row].end() && 
               cols[col].find(num) == cols[col].end() &&
               boxes[boxIndex].find(num) == boxes[boxIndex].end();
    };

    // Helper function to backtrack and fill the grid
    std::function<bool(int, int)> solve = [&](int row, int col) -> bool {
        if (row == 9) return true;  // Solved

        if (col == 9) return solve(row + 1, 0);  // Move to the next row

        if (sudoku[row][col] != 0) return solve(row, col + 1);  // Skip if already filled

        std::vector<int> numbers = {1, 2, 3, 4, 5, 6, 7, 8, 9};
        std::shuffle(numbers.begin(), numbers.end(), gen);  // Randomize the numbers

        // Try placing a number in the cell
        for (int num : numbers)
        {
            if (isValid(row, col, num))
            {
                sudoku[row][col] = num;
                rows[row].insert(num);
                cols[col].insert(num);
                boxes[(row / 3) * 3 + (col / 3)].insert(num);

                if (solve(row, col + 1)) return true;

                // Backtrack
                sudoku[row][col] = 0;
                rows[row].erase(num);
                cols[col].erase(num);
                boxes[(row / 3) * 3 + (col / 3)].erase(num);
            }
        }

        return false;  // No solution found
    };

    solve(0, 0);  // Start filling from the top-left corner
}


void __fastcall TForm1::generating(TObject *Sender)
{
    std::vector<std::vector<int>> sudoku(9, std::vector<int>(9, 0));
    std::vector<std::unordered_set<int>> rows(9), cols(9), boxes(9);

    // Step 1: Generate a random valid Sudoku grid
    generateRandomSudoku(sudoku, rows, cols, boxes);

    // Step 2: Randomly remove cells to create a puzzle
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 8);

    int cellsToRemove = 40 + (std::rand() % 11); // Randomly set number of clues to remove, between 40 and 50
    std::vector<std::pair<int, int>> positions;

    // Generate all possible positions (row, col) for removal
    for (int row = 0; row < 9; ++row)
    {
        for (int col = 0; col < 9; ++col)
        {
            positions.push_back({row, col});
        }
    }

    // Shuffle the positions to randomize the removal order
    std::shuffle(positions.begin(), positions.end(), gen);

    // Remove random cells to create a puzzle
    for (int i = 0; i < cellsToRemove; ++i)
    {
        int row = positions[i].first;
        int col = positions[i].second;

        // Check if the cell is already empty, skip if it is
        if (sudoku[row][col] != 0)
        {
            sudoku[row][col] = 0;  // Remove the number
        }
    }

    // Step 3: Update the display with the generated puzzle
    updateGridDisplay(sudoku);
}

// Function to generate a random valid Sudoku grid


 //mrvhelper functions here
 int getBoxIndex(int row, int col) {
	return (row / 3) * 3 + col / 3;
}

// Initialize hash maps and options for MRV+Hash
void initializeOptions(std::vector<std::vector<int>>& board, std::vector<std::unordered_set<int>>& rows, std::vector<std::unordered_set<int>>& cols, std::vector<std::unordered_set<int>>& boxes,vector<vector<set<int>>>& options){
	for (int row = 0; row < N; row++) {
		for (int col = 0; col < N; col++) {
			if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    int boxIndex = getBoxIndex(row, col);
					if (rows[row].find(num) == rows[row].end() &&
						cols[col].find(num) == cols[col].end() &&
						boxes[boxIndex].find(num) == boxes[boxIndex].end()) {
						options[row][col].insert(num);
		  //vector<vector<set<int>>> options(N, vector<set<int>>(N));
			 }
				}
			}
        }
	}
}
 void placeNumber(vector<vector<int>>& board, int row, int col, int num,vector<unordered_set<int>>& rows, vector<unordered_set<int>>& cols, vector<unordered_set<int>>&boxes,vector<vector<set<int>>>& options) {
	int boxIndex = getBoxIndex(row, col);
	rows[row].insert(num);
	cols[col].insert(num);
	boxes[boxIndex].insert(num);
	board[row][col] = num;

	for (int i = 0; i < N; i++) {
		options[row][i].erase(num);
		options[i][col].erase(num);
		options[(row / 3) * 3 + i / 3][(col / 3) * 3 + i %3].erase(num);
	}
}

// Remove number in MRV+Hash
void removeNumber(vector<vector<int>>& board, int row, int col, int num,vector<unordered_set<int>>& rows,vector<unordered_set<int>>& cols,vector<unordered_set<int>>& boxes,vector<vector<set<int>>>& options) {
    int boxIndex = getBoxIndex(row, col);
	rows[row].erase(num);
	cols[col].erase(num);
	boxes[boxIndex].erase(num);
    board[row][col] = 0;

    for (int i = 0; i < N; i++) {
        //if (board[row][i] == 0)
		 options[row][i].insert(num);
       // if (board[i][col] == 0)
		 options[i][col].insert(num);
        int boxRow = (row / 3) * 3 + i / 3;
        int boxCol = (col / 3) * 3 + i% 3;
       // if (board[boxRow][boxCol] == 0)
		options[boxRow][boxCol].insert(num);
	}
}



bool isValid(int row, int col, int num,vector<unordered_set<int>>& rows,vector<unordered_set<int>>& cols,vector<unordered_set<int>>& boxes) {
	int boxIndex = getBoxIndex(row, col);
	return rows[row].find(num) == rows[row].end() &&
		   cols[col].find(num) == cols[col].end() &&
		   boxes[boxIndex].find(num) == boxes[boxIndex].end();
}

// MRV method to get cell with fewest options
pair<int, int> getMRVCell(vector<vector<set<int>>>& options) {
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


// Sudoku solving functions
bool check(int i, int j, std::unordered_set<int>& rowSet, std::unordered_set<int>& colSet, std::unordered_set<int>& boxSet, int num)
{
	return (rowSet.find(num) == rowSet.end() &&
			colSet.find(num) == colSet.end() &&
			boxSet.find(num) == boxSet.end());
}

bool isValidSudoku(const std::vector<std::vector<int>>& vect)
{
	std::unordered_set<int> rowSets[9], colSets[9], boxSets[9];
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			int num = vect[i][j];
			if (num != 0)
			{
				if (rowSets[i].find(num) != rowSets[i].end()) return false;
				rowSets[i].insert(num);
				if (colSets[j].find(num) != colSets[j].end()) return false;
				colSets[j].insert(num);
				int boxIndex = (i / 3) * 3 + (j / 3);
				if (boxSets[boxIndex].find(num) != boxSets[boxIndex].end()) return false;
				boxSets[boxIndex].insert(num);
			}
		}
	}
	return true;
}

void TForm1::updateGridDisplay(const std::vector<std::vector<int>>& vect)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (vect[i][j] != 0)
			{
				StringGrid1->Cells[j][i] = std::to_string(vect[i][j]).c_str();
			}
			else
			{
				StringGrid1->Cells[j][i] = "";
			}
		}
	}
	Application->ProcessMessages();
	Sleep(5); // Adjust delay as needed for visual effect
}
bool TForm1::solveBackt(std::vector<std::vector<int>>& vect, std::vector<std::unordered_set<int>>& rows, std::vector<std::unordered_set<int>>& cols, std::vector<std::unordered_set<int>>& boxes)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (vect[i][j] == 0)
			{
				for (int k = 1; k <= 9; k++)
				{
					if (check(i, j, rows[i], cols[j], boxes[(i / 3) * 3 + (j / 3)], k))
					{
						vect[i][j] = k;
						rows[i].insert(k);
						cols[j].insert(k);
						boxes[(i / 3) * 3 + (j / 3)].insert(k);
						//Form1->updateGridDisplay(vect); // Show current state

						if (solveBackt(vect, rows, cols, boxes))
							return true;

						vect[i][j] = 0;
						rows[i].erase(k);
						cols[j].erase(k);
						boxes[(i / 3) * 3 + (j / 3)].erase(k);
						//Form1->updateGridDisplay(vect); // Show current state after backtracking
					}
				}
				return false; // No valid number found for this cell
			}
		}
	}
	return true; // Solved
}

bool TForm1::solveBacktracking(std::vector<std::vector<int>>& vect, std::vector<std::unordered_set<int>>& rows, std::vector<std::unordered_set<int>>& cols, std::vector<std::unordered_set<int>>& boxes)
{
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			if (vect[i][j] == 0)
			{
				for (int k = 1; k <= 9; k++)
				{
					if (check(i, j, rows[i], cols[j], boxes[(i / 3) * 3 + (j / 3)], k))
					{
						vect[i][j] = k;
						rows[i].insert(k);
						cols[j].insert(k);
						boxes[(i / 3) * 3 + (j / 3)].insert(k);
						Form1->updateGridDisplay(vect); // Show current state

						if (solveBacktracking(vect, rows, cols, boxes))
							return true;

						vect[i][j] = 0;
						rows[i].erase(k);
						cols[j].erase(k);
						boxes[(i / 3) * 3 + (j / 3)].erase(k);
						Form1->updateGridDisplay(vect); // Show current state after backtracking
					}
				}
				return false; // No valid number found for this cell
			}
		}
	}
	return true; // Solved
}


//MRV + Hash solving method
bool TForm1::solveMRV(std::vector<std::vector<int>>& vect, std::vector<std::unordered_set<int>>& rows, std::vector<std::unordered_set<int>>& cols, std::vector<std::unordered_set<int>>& boxes,vector<vector<set<int>>>& options)
{
	// Placeholder for MRV logic
 pair<int, int> cell = getMRVCell(options);
    if (cell.first == -1) return true;

    int row = cell.first, col = cell.second;

	for (int num : options[row][col]) {
		//if(isFine(vect, row, col, num,rows,cols,boxes,options))
		placeNumber(vect, row, col, num,rows,cols,boxes,options);
		//else
		//continue;
		 Form1->updateGridDisplay(vect);
		 Sleep(10);
		if (solveMRV(vect,rows,cols,boxes,options)) return true;
		removeNumber(vect, row, col, num,rows,cols,boxes,options);
	}
	return false;
}

struct Cell {
    int row, col, possibilities;
    bool operator<(const Cell& other) const {
        return possibilities > other.possibilities; // Min-heap priority
    }
};
bool chk(int i, int j, vector<vector<int>>& grid, int num) {
    for (int x = 0; x < 9; x++) {
        if (grid[i][x] == num || grid[x][j] == num) return false;
    }

    for (int m = (i / 3) * 3; m < ((i / 3) * 3 + 3); m++) {
        for (int n = (j / 3) * 3; n < ((j / 3) * 3 + 3); n++) {
            if (grid[m][n] == num) return false;
        }
    }
    return true;
}
int countPossibilities(int i, int j, vector<vector<int>>& grid) {
    int count = 0;
    for (int num = 1; num <= 9; num++) {
		if (chk(i, j, grid, num)) count++;
    }
    return count;
}


bool TForm1::solveAStar(vector<vector<int>>& grid) {
    priority_queue<Cell> pq;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (grid[i][j] == 0) {
                int possibilities = countPossibilities(i, j, grid);
                pq.push({i, j, possibilities});
            }
        }
    }

    while (!pq.empty()) {
        Cell current = pq.top();
        pq.pop();
        int row = current.row;
        int col = current.col;

        if (grid[row][col] != 0) continue;

        for (int num = 1; num <= 9; num++) {
			if (chk(row, col, grid, num)) {
                grid[row][col] = num;
				//cout << "Placed " << num << " at (" << row << ", " << col << "):" << endl;
			   Form1->updateGridDisplay(grid);

                if (solveAStar(grid)) return true;

                grid[row][col] = 0; // Backtrack
				//cout << "Removed " << num << " from (" << row << ", " << col << "):" << endl;
			   Form1->updateGridDisplay(grid);
            }
        }
        return false;
    }
    return true;
}



void __fastcall TForm1::SolveButtonClick(TObject *Sender)
{
	std::vector<std::vector<int>> sudoku(9, std::vector<int>(9, 0));
	std::vector<std::unordered_set<int>> rows(9), cols(9), boxes(9);

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			String val = StringGrid1->Cells[j][i];
			if (val != "")
			{
				int num = val.ToInt();
				sudoku[i][j] = num;
				rows[i].insert(num);
				cols[j].insert(num);
				boxes[(i / 3) * 3 + (j / 3)].insert(num);
			}
		}
	}

	if (!isValidSudoku(sudoku))
	{
		ShowMessage("Invalid Sudoku input");
		return;
	}

	// Show the second form to choose solving method
	Form3->Show();

}


  void __fastcall TForm1::solvenow(TObject *Sender)
  {
			std::vector<std::vector<int>> sudoku(9, std::vector<int>(9, 0));
	std::vector<std::unordered_set<int>> rows(9), cols(9), boxes(9);
	 std::vector<vector<set<int>>> options(N, vector<set<int>>(N));
	// Fill the sudoku grid from StringGrid1
	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 9; j++)
		{
			String val = StringGrid1->Cells[j][i];
			if (val != "")
			{
				int num = val.ToInt();
				sudoku[i][j] = num;
				rows[i].insert(num);
				cols[j].insert(num);
				boxes[(i / 3) * 3 + (j / 3)].insert(num);
			}
		}
	}
	 if (useBacktracking)
	{



		if (solveBacktracking(sudoku, rows, cols, boxes))
			updateGridDisplay(sudoku);
		else
			ShowMessage("Unable to solve using Backtracking.");
	}
	 if (useMRV)
	{
		initializeOptions(sudoku,rows,cols,boxes,options);
		if (solveMRV(sudoku, rows, cols, boxes,options))
			updateGridDisplay(sudoku);
		else
			ShowMessage("Unable to solve using MRV");
	}
	if(useAStar)
	{
       if (solveAStar(sudoku))
			updateGridDisplay(sudoku);
		else
			ShowMessage("Unable to solve using AStar");
	}
  }
void __fastcall TForm1::StringGrid1KeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	int col = StringGrid1->Col;
	int row = StringGrid1->Row;

	if (Key == VK_UP && row > 0)
	{
		StringGrid1->Row = row - 1;
		Key = 0; // Prevent further processing
	}
	else if (Key == VK_DOWN && row < 8)
	{
		StringGrid1->Row = row + 1;
		Key = 0; // Prevent further processing
	}
	else if (Key == VK_LEFT && col > 0)
	{
		StringGrid1->Col = col - 1;
		Key = 0; // Prevent further processing
	}
	else if (Key == VK_RIGHT && col < 8)
	{
		StringGrid1->Col = col + 1;
		Key = 0; // Prevent further processing
	}
}

void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
	return;
}