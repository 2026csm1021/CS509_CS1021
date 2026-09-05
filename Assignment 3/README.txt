=====================================================================
CS509 - Assignment 3 - Minimum Spanning Tree (Kruskal & Prim)
=====================================================================

SCOPE
-----
This is the individual MST task (Kruskal's algorithm + Prim's
algorithm) as defined in the Assignment 3 specification. Gradient
Descent and Maxflow-Mincut are separate buddy tasks and are not part
of this individual submission.

PROJECT FILES
-------------
Driver.cpp    - Common wrapper / menu driver. Single program entry
                point. Reads input, validates it, builds CSR, runs
                the chosen algorithm(s), prints results.
Graph.h/.cpp  - Adjacency-list Graph struct, file reader, and graph
                validator (range checks, undirected-edge consistency,
                connectivity).
CSR.h/.cpp    - CSR struct and adjacency-list -> CSR converter
                (used as preprocessing, never timed).
MSTTypes.h    - Shared MSTEdge / MSTResult structs used by both
                Kruskal.h and Prim.h (avoids duplicate definitions).
DSU.h/.cpp    - Disjoint Set Union (Union-Find) with path compression
                and union by rank, used by Kruskal.
Kruskal.h/kruskal.cpp - Kruskal's MST algorithm (edge extraction from
                CSR + sort + DSU union all happen inside the timed
                call, as required by the spec).
Prim.h/prim.cpp        - Prim's MST algorithm (min-priority-queue
                based, starts at vertex 0).
Input/        - Test input files (see table below).

HOW TO COMPILE
---------------
    g++ -std=c++17 *.cpp -o assignment3

Compiles cleanly with -Wall -Wextra, no warnings.

HOW TO RUN
----------
Interactive menu:
    ./assignment3
    -> choose 1 (Kruskal), 2 (Prim), 3 (Both), or 4 (Exit)
    -> then type the input file path, e.g. Input/mst_10.txt

Command-line mode (skips the menu):
    ./assignment3 <choice> <input_file>
    choice: 1 = Kruskal, 2 = Prim, 3 = Both
    Example:
    ./assignment3 3 Input/mst_10.txt

TIMING METHODOLOGY
-------------------
Only the algorithm call itself is timed with std::chrono
high_resolution_clock. File reading, input validation, and the
adjacency-list -> CSR conversion happen once, BEFORE any timer
starts, and are shared between Kruskal and Prim so both run on the
exact same prepared CSR graph. For Kruskal, extracting edges from
CSR and sorting them happen inside kruskalMST() and are therefore
included in the timed Kruskal call, per the spec.

9.1 MST RESULTS TABLE
----------------------
All graphs are connected, sparse (E approx 2V-4V), randomly
generated with integer weights in [1,100], except mst_1.txt which is
the 5-vertex example graph from the assignment PDF (expected weight
16, verified below).

File             V       E        Kruskal Wt   Prim Wt    Kruskal Time  Prim Time    Equal?   Status
mst_1.txt        5       7        16           16         0.008 ms      0.016 ms     Yes      Pass
mst_10.txt       10      25       184          184        0.013 ms      0.034 ms     Yes      Pass
mst_100.txt      100     300      1776         1776       0.089 ms      0.407 ms     Yes      Pass
mst_10000.txt    10,000  30,000   198,516      198,516    9.599 ms      68.979 ms    Yes      Pass
mst_50000.txt    50,000  150,000  1,007,467    1,007,467  52.015 ms     406.383 ms   Yes      Pass
mst_100000.txt   100,000 300,000  2,019,012    2,019,012  111.171 ms    859.659 ms   Yes      Pass

Notes:
- mst_1.txt is the exact PDF example (section 5.2/5.3); expected
  total weight 16 was confirmed against our output.
- For the randomly generated graphs there is no independently known
  "expected" weight, so correctness is verified by Kruskal and Prim
  agreeing on the same minimum total weight from the same CSR graph.
- Prim is consistently slower than Kruskal here. This is expected:
  our Prim implementation uses a simple binary heap (no decrease-key),
  so it can push several stale entries per vertex, while Kruskal's
  edge count is bounded by E and DSU operations are nearly O(1).
- All test cases above were actually compiled and executed on this
  machine; no numbers were estimated or assumed.

VALIDATION PERFORMED BY THE PROGRAM
-------------------------------------
- File can be opened (else: clear error, no crash).
- V and E can be parsed.
- Every vertex id and neighbour id is within [0, V).
- No self-loops.
- Every undirected edge (u,v,w) appears in both endpoints'
  adjacency lists with the same weight.
- The graph is connected (BFS reachability check from vertex 0).
- Kruskal and Prim also each report `connected = false` internally
  if they end up with fewer than V-1 MST edges, so a disconnected
  graph is never silently reported as a valid MST.

BONUS: NEGATIVE / ZERO WEIGHT TEST
------------------------------------
Input/mst_negzero_test.txt (4 vertices, 4 edges) mixes negative,
zero and positive weights to confirm both algorithms handle them
correctly (MST weight can legitimately be negative).

File                      V   E   Kruskal Wt   Prim Wt   Equal?   Status
mst_negzero_test.txt      4   4   -7           -7        Yes      Pass
