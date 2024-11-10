
# Sudoku Solver

## 📋 Overview

The **Sudoku Solver** application is a comprehensive tool designed to help you solve, generate, and play Sudoku puzzles. It provides an interactive experience for Sudoku enthusiasts by offering multiple solving algorithms, a play mode, and a unique feature to **visualize the solving process step-by-step**, making it an excellent resource for comparing different algorithmic approaches.

### 🚀 Features

1. **Generate Sudoku Puzzles**: 
   - Instantly create new Sudoku puzzles  to challenge yourself.

2. **Solve Sudoku Puzzles**:
   - Input a Sudoku puzzle manually or load one to be solved by the program.
   - Choose from four advanced solving algorithms:
     - **Backtracking**: A classic brute-force approach.
     - **MRV (Minimum Remaining Values)**: An optimized backtracking method utilizing heuristics.
     - **A* Search Algorithm**: A pathfinding approach that considers both constraints and potential solutions.
     - **BFS (Breadth-First Search)**: An iterative approach to find the solution layer by layer.

3. **Play Mode**:
   - Solve a generated Sudoku puzzle manually and get real-time feedback on your moves.

4. **Algorithm Visualization**:
   - Watch the entire solving process on the screen as the numbers update dynamically. 
   - Visual feedback helps in understanding the behavior of different algorithms, making it easier to compare their performance and efficiency in solving the puzzle.

### 🛠️ Data Structures Used

The application leverages several efficient data structures to enhance solving capabilities:
- **Vectors**: For dynamic storage of Sudoku grids.
- **Hash Maps**: To track potential values for cells, constraints, and row/column possibilities.
- **Priority Queues**: Utilized in the A* search algorithm to prioritize nodes based on their heuristic scores.
- **Queues**: Employed in the BFS algorithm for exploring nodes level by level.

## 🔧 Getting Started

Follow these steps to set up the Sudoku Solver on your local machine.

### Prerequisites

- C++ compiler (g++ or similar)
- RAD Studio (if using the UI-based application)

Installation:
Install RAD Studio on your machine.
Download and install the executable file (sudoku_solver.exe) available in the repository.
Run sudoku_solver.exe to start the application.

## 🧩 Usage

1. **Generating a Puzzle**:
   - Select the 'Generate' option from the menu to create a new Sudoku puzzle.

2. **Solving a Puzzle**:
   - Enter your Sudoku puzzle manually or choose an existing one.
   - Select your preferred solving algorithm: Backtracking, MRV, A*, or BFS.
   - The solving process is visualized step-by-step, allowing you to observe how each algorithm approaches the problem differently.

3. **Play Mode**:
   - Choose the 'Play' option to manually solve a generated puzzle.
   - The system checks your inputs and provides instant feedback on correctness.

4. **Algorithm Comparison**:
   - By visualizing each solving method, you can directly compare the efficiency and behavior of different algorithms.
   - This feature helps in understanding the strengths and weaknesses of each approach based on the time taken and the number of updates made on the grid.

## 📚 Algorithms Explained

### 1. **Backtracking**:
   - A depth-first search approach that tries filling each cell and backtracks if a contradiction is found.

### 2. **Minimum Remaining Values (MRV)**:
   - An enhancement of backtracking that prioritizes cells with the fewest possible values, reducing the search space.

### 3. **A* Search**:
   - Uses a heuristic function to explore nodes with the lowest cost and potential to reach the solution faster.

### 4. **Breadth-First Search (BFS)**:
   - Iteratively explores all possibilities layer by layer, ensuring the first solution found is the shortest path.

## 📈 Data Structure Overview

- **Vectors**: Used for dynamic arrays to store the Sudoku grid.
- **Hash Maps**: Store constraints, such as possible values for each cell, to minimize recalculations.
- **Priority Queues**: Manage the open set in A* to retrieve the node with the lowest cost efficiently.
- **Queues**: Implement BFS to explore all possibilities at each level.

## 💻 Contributing

Contributions are welcome! If you have suggestions or improvements, feel free to create a pull request.



## 👨‍💻 Author

- Vadlamudi Jyothsna
- Shruti Vibhute
- Gnani Prakash

