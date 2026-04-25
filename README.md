# ceng383
# SSSP Performance Analysis (DIMACS Road Networks)

This repository contains the C++ implementation and performance analysis of Single-Source Shortest Path (SSSP) algorithms for the **SENG383 / CENG383** course project. The project evaluates the theoretical and practical performance differences between **Dijkstra's Algorithm** and the **Bellman-Ford Algorithm**.

## Project Overview

The main objective is to measure the runtime and memory consumption of both algorithms on extremely large, sparse graphs. 
* **Dijkstra's Algorithm:** Implemented using a Min-Heap (Priority Queue).
* **Bellman-Ford Algorithm:** Implemented with an early-exit optimization to prevent redundant iterations.

## Performance Results & Scalability

The algorithms were tested on two different datasets from the 9th DIMACS Implementation Challenge to evaluate scalability:
1. **New York (NY):** ~264K nodes
2. **Florida (FLA):** ~1.07M nodes

| Dataset | Algorithm | Runtime | Memory Load |
| :--- | :--- | :--- | :--- |
| **New York** | Dijkstra | ~118 ms | ~25 MB |
| **New York** | Bellman-Ford | ~3,774 ms | ~25 MB |
| **Florida** | Dijkstra | ~483 ms | ~83 MB |
| **Florida** | Bellman-Ford | ~43,258 ms | ~83 MB |

### Conclusion
As the dataset scales from NY to FLA (approximately a 4x increase in size), Dijkstra's execution time scales linearly. In contrast, Bellman-Ford exhibits a massive exponential increase in runtime, proving that Dijkstra is vastly superior and more efficient for massive, sparse road networks.

## How to Run the Code

1. Clone the repository:
   ```bash
   git clone [https://github.com/zeynpkara/ceng383.git](https://github.com/zeynpkara/ceng383.git)
   ```

2. Compile the source code using `g++` with the `-O3` optimization flag:
   ```bash
   g++ -O3 main.cpp -o sssp_analysis
   ```

3. Run the executable:
   ```bash
   ./sssp_analysis
   ```

*Note: The `.gr` dataset files from the DIMACS challenge are required to run the code. Due to GitHub's file size limits, they are not included in this repository. Please download them (e.g., `USA-road-d.FLA.gr`) and update the file path in `main.cpp` before running.*
