# CS509 Assignment 4

## Tasks

This folder contains the individual Assignment 4 tasks:

- Vertex Coloring: Welsh-Powell ordering followed by greedy coloring.
- PageRank: iterative PageRank on a directed, unweighted graph.
- CSR conversion is used as preprocessing and is not included in algorithm timing.

## Files

- `Graph.h/.cpp` - adjacency-list input and validation.
- `CSR.h/.cpp` - adjacency-list to CSR conversion.
- `VertexColoring.h/.cpp` - Vertex Coloring algorithm.
- `PageRank.h/.cpp` - PageRank algorithm.
- `Driver.cpp` - menu driver for both algorithms.
- `input/` - test input files.

## Vertex Coloring test cases

The required vertex counts are 10, 100, 10,000, 50,000 and 100,000.
The specification asks large graphs to remain sparse, approximately E = 2V to 4V where practical.

| File | V | E | Graph type |
|---|---:|---:|---|
| `coloring_10.txt` | 10 | 10 | Undirected, unweighted |
| `coloring_100.txt` | 100 | 200 | Undirected, unweighted |
| `coloring_1000.txt` | 1,000 | 2,000 | Undirected, unweighted |
| `coloring_10000.txt` | 10,000 | 20,000 | Undirected, unweighted |
| `coloring_50000.txt` | 50,000 | 100,000 | Undirected, unweighted |
| `coloring_100000.txt` | 100,000 | 200,000 | Undirected, unweighted |

`coloring.txt` is the small example/test input.

## PageRank test cases

The required vertex counts are 10, 100, 1,000, 10,000 and 50,000. The 100,000-vertex case is optional.
The specification requires large PageRank graphs to be sparse but does not prescribe one exact E value. For the generated benchmark files below, E = 2V was chosen as a sparse test property.

| File | V | E | Graph type | Parameters |
|---|---:|---:|---|---|
| `pagerank_10.txt` | 10 | 20 | Directed, unweighted | d=0.85, tolerance=0.000001, max=100 |
| `pagerank_100.txt` | 100 | 200 | Directed, unweighted | d=0.85, tolerance=0.000001, max=100 |
| `pagerank_1000.txt` | 1,000 | 2,000 | Directed, unweighted | d=0.85, tolerance=0.000001, max=100 |
| `pagerank_10000.txt` | 10,000 | 20,000 | Directed, unweighted | d=0.85, tolerance=0.000001, max=100 |
| `pagerank_50000.txt` | 50,000 | 100,000 | Directed, unweighted | d=0.85, tolerance=0.000001, max=100 |

`pagerank.txt` is the small example/test input and `pagerank_dangling.txt` tests zero-outdegree handling.

## Compilation

```text
g++ -std=c++17 Driver.cpp CSR.cpp Graph.cpp VertexColoring.cpp PageRank.cpp -o assignment4
```

Run:

```text
./assignment4
```

Choose `1` for Vertex Coloring or `2` for PageRank, then enter the input file path.

## Verified benchmark runs

The implementation was compiled with `-Wall -Wextra` without warnings in the verification environment.

Observed algorithm times in that environment:

| Algorithm | V | Observed time |
|---|---:|---:|
| Vertex Coloring | 10 | 0.002323 ms |
| Vertex Coloring | 100 | 0.029273 ms |
| Vertex Coloring | 1,000 | 0.326434 ms |
| Vertex Coloring | 10,000 | 3.63206 ms |
| Vertex Coloring | 50,000 | 21.2121 ms |
| Vertex Coloring | 100,000 | 47.5126 ms |
| PageRank | 10 | 0.008182 ms |
| PageRank | 100 | 0.322438 ms |
| PageRank | 1,000 | 7.68433 ms |
| PageRank | 10,000 | 731.038 ms |
| PageRank | 50,000 | 18,606.4 ms |

Execution time is machine-dependent; use the timings from the submission machine in the final report if required.
