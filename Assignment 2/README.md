# CS509 - Assignment 2

## 1. Overview

This repository contains the individual-task implementation for CS509 Assignment 2:

- Bellman-Ford — single-source shortest path
- Floyd-Warshall — all-pairs shortest path
- CSR (Compressed Sparse Row) representation for the CSR-based graph input

The driver automatically scans `testcase/input`, identifies `bf_input_*.txt` and `fw_input_*.txt`, runs the corresponding algorithm, and writes results to `testcase/output`.

The assignment requires that only algorithm execution time be measured. File reading, parsing, CSR conversion, matrix construction, output printing, and file writing are excluded from the reported time. 

## 2. Project Structure

```text
Assignment 2/
├── driver.cpp
├── graph.cpp
├── graph.h
├── csr.cpp
├── csr.h
├── bellmanFord.cpp
├── bellmanFord.h
├── Floyd_Warshall.cpp
├── Floyd_Warshall.h
├── README.md
└── testcase/
    ├── input/
    │   ├── bf_input_1.txt
    │   ├── bf_input_2.txt
    │   ├── bf_input_3.txt
    │   ├── bf_input_4.txt
    │   ├── fw_input_1.txt
    │   ├── fw_input_2.txt
    │   ├── fw_input_3.txt
    │   └── fw_input_4.txt
    └── output/
        ├── output_1.txt
        ├── output_2.txt
        └── ...
```

## 3. Algorithms

### Bellman-Ford

Bellman-Ford computes shortest distances from one source to every reachable vertex and supports negative edge weights.

The algorithm relaxes all edges `V-1` times and then performs an additional pass to detect a reachable negative-weight cycle.

**Complexity:** `O(V × E)`

Bellman-Ford uses a directed weighted adjacency-list input, which is converted to CSR before the algorithm timer starts. [CS509 Assignment 2, pp. 1, 4-5]

### Floyd-Warshall

Floyd-Warshall computes shortest distances between every pair of vertices.

For every intermediate vertex `k`:

```text
dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j])
```

After completion, a negative value on `dist[i][i]` indicates a negative-weight cycle.

**Complexity:** `O(V³)` time and `O(V²)` memory.

Floyd-Warshall reads its dense adjacency matrix directly and does not require CSR conversion. [CS509 Assignment 2, pp. 1-2, 4, 6-7]

## 4. CSR Representation

CSR stores a sparse graph using:

- `row_ptr` — start/end positions of each vertex's neighbours
- `col_idx` — destination vertices
- `values` — edge weights

The adjacency-list-to-CSR conversion is preprocessing and is not included in the algorithm execution time. [CS509 Assignment 2, pp. 2, 4]

## 5. Input Format

### Bellman-Ford

Bellman-Ford uses a directed weighted adjacency-list format:

```text
V E
u0 degree neighbor1 weight1 neighbor2 weight2 ...
u1 degree neighbor1 weight1 neighbor2 weight2 ...
...
u(V-1) degree ...
SOURCE s
```

Example:

```text
5 10
0 2 1 6 3 7
1 3 2 5 3 8 4 -4
2 1 1 -2
3 2 2 -3 4 9
4 2 0 2 2 7
SOURCE 0
```

Vertices are numbered `0` through `V-1`. Negative weights are allowed on directed edges. [CS509 Assignment 2, pp. 5-6]

### Floyd-Warshall

Floyd-Warshall uses a dense `V × V` matrix:

```text
V
row 0
row 1
...
row V-1
```

Use `INF` when no direct edge exists and `0` on the diagonal.

Example:

```text
5
0 3 8 INF -4
INF 0 INF 1 7
INF 4 0 INF INF
2 INF -5 0 INF
INF INF INF 6 0
```

[CS509 Assignment 2, p. 6]

## 6. Running the Program

Open PowerShell inside the Assignment 2 directory.

### Compile

```powershell
g++ -std=c++17 driver.cpp graph.cpp csr.cpp bellmanFord.cpp Floyd_Warshall.cpp -o runc
```

### Run

```powershell
.
unc.exe
```

The program automatically scans:

```text
testcase/input
```

and writes results to:

```text
testcase/output
```

No input filename needs to be supplied on the command line.

## 7. Test-File Naming

The current driver uses:

```text
bf_input_*.txt  -> Bellman-Ford
fw_input_*.txt  -> Floyd-Warshall
```

For example:

```text
bf_input_1.txt
bf_input_2.txt
bf_input_3.txt
bf_input_4.txt

fw_input_1.txt
fw_input_2.txt
fw_input_3.txt
fw_input_4.txt
```

## 8. Output

### Bellman-Ford

A normal result contains:

```text
Algorithm: Bellman-Ford
Vertices: ...
Edges: ...
Source: ...
Negative Cycle: No

Vertex    Distance
0         ...
1         ...
...
```

If a reachable negative cycle is found, the distance table should be omitted and the negative-cycle result reported.

### Floyd-Warshall

A normal result contains:

```text
Algorithm: Floyd-Warshall
Vertices: ...
Negative Cycle: No

Distance Matrix:
...
```

If a negative cycle is found, the distance matrix should be omitted. [CS509 Assignment 2, pp. 5-7]

## 9. Timing

The timer is placed immediately before the algorithm call and stopped immediately after the algorithm completes, including the negative-cycle check.

Not included:

- file reading
- input parsing
- CSR conversion
- matrix construction
- result printing
- file writing
- other setup work


## 10. Required Graph Sizes

### Bellman-Ford

```text
10
100
10,000
50,000
100,000
```

The two largest graphs should remain sparse, approximately `E ≈ 2V to 4V`.

### Floyd-Warshall

```text
10
100
500
1,000
2,000
```

These reduced sizes are required because Floyd-Warshall has `O(V³)` time and `O(V²)` memory complexity. [CS509 Assignment 2, p. 4]

## 11. Results Table

The table below is filled from the actual input and output files used in the current run.

| Algorithm | Test File | Output File | V | E | Source | Negative Cycle | Expected Output | Actual Output | Time | Status |
|---|---|---|---:|---:|---:|---|---|---|---:|---|
| Bellman-Ford | bf_input_1.txt | output_1.txt | 5 | 7 | 0 | No | Shortest distances | 0:0, 1:4, 2:2, 3:9, 4:11 | 0.002400 ms | Pass |
| Bellman-Ford | bf_input_2.txt | output_2.txt | 6 | 4 | 0 | No | Shortest distances | 0:0, 1:3, 2:5, 3:9, 4:INF, 5:INF | 0.001800 ms | Pass |
| Bellman-Ford | bf_input_3.txt | output_3.txt | 5 | 10 | 0 | No | Shortest distances | 0:0, 1:2, 2:7, 3:4, 4:-2 | 0.002400 ms | Pass |
| Bellman-Ford | bf_input_4.txt | output_4.txt | 7 | 11 | 0 | No | Shortest distances | 0:0, 1:2, 2:4, 3:1, 4:5, 5:6, 6:9 | 0.002700 ms | Pass |
| Floyd-Warshall | fw_input_1.txt | output_5.txt | 5 | 7 | N/A | No | Distance matrix | 5×5 matrix | 0.012700 ms | Pass |
| Floyd-Warshall | fw_input_13.txt | output_6.txt | 5 | 12 | N/A | No | Distance matrix | 5×5 matrix | 0.004500 ms | Pass |
| Floyd-Warshall | fw_input_2.txt | output_7.txt | 7 | 17 | N/A | No | Distance matrix | 7×7 matrix | 0.006200 ms | Pass |
| Floyd-Warshall | fw_input_4.txt | output_8.txt | 6 | 4 | N/A | No | Distance matrix | 6×6 matrix | 0.002900 ms | Pass |

### Bellman-Ford Output Details

- `bf_input_1.txt`: distances = `[0, 4, 2, 9, 11]`; no negative cycle. fileciteturn5file8L1-L14
- `bf_input_2.txt`: distances = `[0, 3, 5, 9, INF, INF]`; no negative cycle. fileciteturn5file9L1-L15
- `bf_input_3.txt`: distances = `[0, 2, 7, 4, -2]`; no negative cycle. fileciteturn5file10L1-L14
- `bf_input_4.txt`: distances = `[0, 2, 4, 1, 5, 6, 9]`; no negative cycle. fileciteturn5file11L1-L16

### Floyd-Warshall Output Details

- `fw_input_1.txt`: 5×5 distance matrix; no negative cycle. fileciteturn5file12L1-L12
- `fw_input_13.txt`: 5×5 distance matrix; no negative cycle. fileciteturn5file13L1-L12
- `fw_input_2.txt`: 7×7 distance matrix; no negative cycle. fileciteturn5file14L1-L14
- `fw_input_4.txt`: 6×6 distance matrix; no negative cycle. fileciteturn5file15L1-L13

For Floyd-Warshall, the edge count in the table is the number of finite off-diagonal entries in the input matrix. The input files confirm the corresponding graph sizes and edge counts for Bellman-Ford. For example, `bf_input_1.txt` contains `5 7` and `SOURCE 0`; `bf_input_2.txt` contains `6 4` and `SOURCE 0`; `bf_input_3.txt` contains `5 10` and `SOURCE 0`; and `bf_input_4.txt` contains `7 11` and `SOURCE 0`. fileciteturn5file0L1-L7 fileciteturn5file1L1-L8 fileciteturn5file2L1-L7 fileciteturn5file3L1-L9

## 13. Negative-Cycle Testing

Bellman-Ford detects a reachable negative-weight cycle during its extra relaxation pass.

Floyd-Warshall detects a negative-weight cycle by checking whether any:

```text
dist[i][i] < 0
```

after the algorithm finishes.

For a negative-cycle test case, the distance table/matrix should be omitted as required by the specification. [CS509 Assignment 2, pp. 5-7]

## 14. Environment

```text
Operating System : Windows
CPU              : AMD Ryzen 5 5600H
RAM              : 8 GB
C++ Standard     : C++17
Compiler         : MinGW-w64 / GCC
```

Check the installed compiler with:

```powershell
g++ --version
```
