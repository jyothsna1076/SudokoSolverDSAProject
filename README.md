Group 6: Sudoku Solver
Objective:
Our goal is to develop an efficient C++ program capable of solving Sudoku puzzles through the backtracking algorithm. Sudoku is a 9x9 grid-based logic puzzle that requires each row, column, and 3x3 subgrid to contain unique numbers from 1 to 9. This project emphasizes developing a solution that not only solves Sudoku puzzles but also provides a step-by-step, visual representation of the solving process through an interactive user interface (UI). This approach aims to optimize efficiency using techniques like heuristic methods and advanced data structures, making the program both educational and functional. The Sudoku solver has broader implications in artificial intelligence, combinatorial optimization, and constraint satisfaction problems.


Data Sources and Testing Framework:
Our dataset consists of publicly available Sudoku puzzles from sources such as Kaggle. This collection includes puzzles categorized by difficulty (easy, medium, hard). The dataset serves to rigorously test the solver's accuracy and efficiency across varying levels of complexity, with more challenging puzzles posing significant tests due to fewer initial clues and greater complexity.
Source: Online repositories, including Kaggle.
Content: Puzzles classified by difficulty level.
Challenges: Harder puzzles increase testing rigor, revealing potential optimizations needed for complex cases.

Approach and Design of Solution:
Our solution follows a structured approach, which we break down into multiple phases:
Sudoku Grid Representation:
The 9x9 grid is represented as a 2D array. Cells are initialized to 0 (or blank) for empty entries, while pre-filled cells contain values from 1 to 9.
Each cell follows the Sudoku rule that each number must be unique in its row, column, and 3x3 subgrid.
Backtracking Algorithm:
The algorithm recursively tries to fill each cell with a number, checking if each attempt follows Sudoku rules.
If a conflict arises, it removes the last entry and tries the next possible number.
This process continues until all cells are filled, or no valid solution exists for the given configuration.
Heuristic Optimizations:
Minimum Remaining Values (MRV): MRV selects the cell with the fewest valid numbers, often reducing the search space and leading to quicker solutions.
Degree Heuristic: For cells with equal MRV, the degree heuristic prioritizes those that influence the most unfilled cells, further enhancing the efficiency of the solution.
Constraint Propagation:
Each time a number is assigned to a cell, that number is immediately removed from possible values for all related cells in the same row, column, and subgrid.
This early elimination helps prevent conflicts and reduces backtracking.
Data Structure Integration:
A hash map or set is used to store the possible values for each empty cell, dynamically updating as the algorithm progresses. This storage avoids recomputation, improving efficiency by reducing redundant checks.
User Interface (UI) and Step-by-Step Visualization:
The UI allows users to input puzzles and provides a visual, step-by-step representation of how the algorithm solves the puzzle.
Users can observe the filling of cells and the effects of each constraint, enhancing understanding of the algorithm’s functionality and logic.
Validation of Solution:
After completing the algorithm, a final validation checks all rows, columns, and subgrids to confirm that the solution meets Sudoku’s requirements, ensuring correctness and completeness.

Observations and Results:
After testing across puzzles of different difficulty levels, we observe:
Efficiency: The algorithm solves easy and medium-level puzzles efficiently, while hard puzzles take more time due to the increased complexity.
Effectiveness of Heuristics: The combined use of MRV and Degree heuristics significantly reduces the number of steps needed to solve challenging puzzles.
UI Effectiveness: The visual step-by-step solving process is intuitive and aids users in understanding how backtracking algorithms operate in constraint satisfaction contexts.
Areas for Further Optimization: Hard puzzles reveal opportunities to improve constraint propagation and explore additional heuristics for efficiency gains.

Conclusion:
Our C++ Sudoku solver leverages the backtracking algorithm enhanced with MRV and Degree heuristics and uses hash maps for tracking possible values, resulting in a faster and more optimized solution. The interactive UI provides an educational and engaging user experience, making the algorithm’s solving process easy to follow. Future improvements may include exploring more advanced optimization techniques and extending the algorithm to handle larger grids and more complex variants of Sudoku.
This project provides a robust platform for demonstrating the effectiveness of algorithmic problem-solving in recreational and AI applications.

