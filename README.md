# Sudoku Solver
### Objective:
This project aims to develop an efficient Sudoku solver in C++ that uses the backtracking algorithm with enhancements like heuristic methods and advanced data structures. Sudoku is a popular 9x9 grid-based puzzle where each row, column, and 3x3 subgrid must contain unique numbers from 1 to 9. Besides solving Sudoku puzzles, our solution will provide a step-by-step, interactive visualization to help users understand the solving process. This project highlights the importance of constraint satisfaction, combinatorial optimization, and problem-solving techniques in artificial intelligence (AI) and computer science.

### Data Sources and Testing Framework:
The accuracy and robustness of our solution are evaluated with a dataset of Sudoku puzzles sourced from publicly available repositories like Kaggle. This dataset includes puzzles classified by difficulty (easy, medium, hard), allowing us to test the algorithm's performance across varying complexity levels. More challenging puzzles present unique testing difficulties due to fewer initial clues, requiring sophisticated handling for efficiency.

* Source: Online repositories such as Kaggle.
* Content: A collection of Sudoku puzzles categorized by difficulty.
* Challenges: Hard puzzles pose greater testing rigor, revealing the solver’s performance and the need for further optimization under increased complexity.
## Approach and Design of Solution
Our approach is divided into structured phases to ensure clarity and efficiency:

### 1. Sudoku Grid Representation
* The 9x9 grid is represented as a 2D array.
* Cells are initialized to 0 (or blank) for empty entries; pre-filled cells contain values from 1 to 9.
* Each cell is constrained by the Sudoku rule: each number must be unique within its row, column, and 3x3 subgrid.
### 2. Backtracking Algorithm
* The algorithm applies a recursive approach, attempting to fill each cell while following Sudoku rules.
* When a conflict arises, it backtracks by removing the last entry and tries the next possible number.
* This process continues until the grid is completed, or it determines there is no valid solution for the given configuration.
### 3. Heuristic Optimizations
To improve efficiency, we incorporate heuristic techniques that help minimize the search space:

Minimum Remaining Values (MRV): This heuristic prioritizes the cell with the fewest valid number options, helping the solver to reduce search depth by tackling constrained cells first.
Degree Heuristic: When multiple cells have the same MRV, this heuristic prioritizes the cell that influences the most unfilled cells, further enhancing efficiency by focusing on high-impact choices.
## 4. Constraint Propagation
* Whenever a number is assigned to a cell, that number is immediately removed from possible values for all related cells in the same row, column, and 3x3 subgrid.
* This elimination helps prevent conflicts early, reducing the need for backtracking by maintaining constraints at each step.
### 5. Data Structure Integration
* We use a hash map or set to store possible values for each empty cell. This dynamic storage is updated as the algorithm progresses, preventing redundant calculations and improving efficiency.
### 6. User Interface (UI) and Step-by-Step Visualization
The interactive UI allows users to input puzzles and view the algorithm’s progress in real time.
* A step-by-step visualization displays how each cell is filled, providing insights into constraint satisfaction and the logic behind the backtracking algorithm.
### 7. Validation of Solution
* After completing the solution, the program performs a final validation to ensure that all rows, columns, and subgrids meet Sudoku requirements, confirming the solution’s accuracy.
## Observations and Results
Our solver performs well across puzzles of varying difficulty, and our findings highlight the following:

* Efficiency: The algorithm quickly solves easy and medium puzzles. Harder puzzles take more time due to increased complexity, which is expected given the reduced number of initial clues.
* Effectiveness of Heuristics: The combined use of MRV and Degree heuristics significantly decreases the number of steps required to solve more difficult puzzles, making the algorithm more efficient.
* UI Effectiveness: The step-by-step visualization offers an intuitive user experience, effectively demonstrating how backtracking and constraint satisfaction work together to solve Sudoku.
* Areas for Further Optimization: The algorithm's performance on hard puzzles reveals potential areas for optimization, such as enhancing constraint propagation or exploring additional heuristic methods.
## Conclusion
Our C++ Sudoku solver demonstrates an efficient approach to solving Sudoku through a backtracking algorithm, enhanced by MRV and Degree heuristics and supported by a dynamic data structure for tracking possible values. The interactive UI offers a user-friendly, educational interface that enables users to follow the algorithm’s logic and understand constraint satisfaction principles. This project successfully illustrates algorithmic problem-solving techniques and can serve as a foundation for exploring more complex AI and optimization applications.

### Future Enhancements:
Future work may focus on further optimizing constraint propagation, experimenting with advanced heuristics, and extending the algorithm to handle larger grid sizes or different Sudoku variants. This project provides a solid platform for showcasing constraint satisfaction and optimization in both recreational and professional contexts, with implications for AI, combinatorial problem-solving, and educational tools.






