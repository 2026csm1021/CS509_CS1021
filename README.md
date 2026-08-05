# CS509 – Assignment 1 (Individual Part)

## GEMM (Simple + Blocking) and CSR Graph Conversion

This repository contains the **individually evaluated** portion of CS509 Assignment 1, as defined
in the assignment specification (*Single Task: GEMM*). The implementation includes:

- General Matrix Multiplication (GEMM)
  - Simple (direct triple-loop) implementation
  - Blocking / tiled implementation
- CSR (Compressed Sparse Row) conversion helper for graph inputs (used by the buddy‑task
  algorithms BFS / DFS / SSSP)

Every result below was produced by actually building the code and running it — nothing here is
estimated, guessed, or copied from the assignment document.

---

## Project Structure

```
CS509_CS1021/
│
├── include/
│   ├── gemm.h          # GEMM function declarations
│   └── csr.h            # Graph / CSRGraph structs + function declarations
│
├── src/
│   ├── wrapper.cpp       # main() – menu driver (choice 1 = GEMM, choice 2 = CSR)
│   ├── run_gemm.cpp      # runGEMM(): loops over input/gemm_test_1..8.txt
│   ├── gemm.cpp          # simpleMatrix() and blockingMatrix() implementations
│   └── csr.cpp           # readGraph() and buildCSR()
│
├── input/
│   ├── gemm_test_1.txt … gemm_test_8.txt     # GEMM test cases
│   └── input.txt                              # CSR demo graph (see note below)
│
├── output/
│   └── output_1.txt … output_8.txt            # GEMM results (regenerated each run)
│
├── driver.exe            # prebuilt Windows binary
├── .gitignore
└── README.md
```

---

## Build Instructions

The prebuilt `driver.exe` in this repo is a Windows binary. To build from source (Linux/macOS/WSL),
use the **actual** source file names present in this repo:

```bash
g++ -O2 -std=c++17 -Iinclude src/wrapper.cpp src/gemm.cpp src/csr.cpp src/run_gemm.cpp -o driver
```

This is the exact command used to build and test everything reported below.

---

## Run Instructions

The program is **menu-driven** — it reads the choice from standard input, it does **not** take
command-line arguments for an input file. Run it and type `1` or `2`:

```
./driver
   CS509 Assignment 1
1. GEMM
2. CSR
 Enter Choice: 1
```

- **Choice 1 (GEMM):** `runGEMM()` automatically loops over the 8 fixed test files
  `input/gemm_test_1.txt` … `input/gemm_test_8.txt`, using a hardcoded block size of **32**, and
  writes `output/output_1.txt` … `output/output_8.txt`.
- **Choice 2 (CSR):** reads a single hardcoded file, `input/input.txt`, builds the `Graph`, converts
  it to CSR, and prints `row_ptr` / `col_idx` / `values` to the console.

> **Note on `input/input.txt`:** this file was not present in the uploaded project (only the
> `gemm_test_*.txt` files existed). Running Choice 2 against the unmodified project fails with
> `File not found!` — this was reproduced directly before making any changes. To verify the CSR
> code path actually works, a demo graph file was added using the exact worked example from the
> assignment spec (Sections 2.3 / 6.2):
> ```
> 5 5
> 0 2 1 2
> 1 2 0 3
> 2 3 0 3 4
> 3 2 1 2
> 4 1 2
> SOURCE 0
> ```
> Before final submission, replace `input/input.txt` with the real graph input(s) intended for the
> CSR-consuming buddy-task algorithms, and update the CSR results table below accordingly.

---

## Timing Methodology

Execution time is measured with `std::chrono::high_resolution_clock`, started immediately before
the call to `simpleMatrix()` / `blockingMatrix()` and stopped immediately after it returns. File
reading, input parsing, and result printing are **not** included in the timed region, consistent
with the assignment's timing rule. Times are reported in milliseconds, from a single run per test
file (no averaging was applied).

Times for the smallest test cases (well under a millisecond) sit close to the resolution of the
system clock and are affected by cache/branch-prediction "warm-up," so they fluctuate more between
runs than the larger cases do. The larger cases (200×200×200 and above) were observed to be stable
to within roughly 5–10% across repeated runs.

---

## GEMM Results

Run performed with `blockSize = 32` on the machine used to test this submission. All 8 test files
supplied in `input/` were exercised in a single run of `./driver` with choice `1`.

| Test File | M × K × N | Simple Time | Blocking Time | Block Size | Status |
|---|---|---:|---:|---:|:---:|
| gemm_test_1.txt | 10 × 10 × 10 | 0.001673 ms | 0.001425 ms | 32 | ✅ Pass |
| gemm_test_2.txt | 20 × 30 × 15 | 0.006643 ms | 0.007558 ms | 32 | ✅ Pass |
| gemm_test_3.txt | 50 × 50 × 50 | 0.074805 ms | 0.099049 ms | 32 | ✅ Pass |
| gemm_test_4.txt | 100 × 80 × 120 | 0.524945 ms | 0.767584 ms | 32 | ✅ Pass |
| gemm_test_5.txt | 200 × 200 × 200 | 10.5316 ms | 10.8997 ms | 32 | ✅ Pass |
| gemm_test_6.txt | 300 × 150 × 250 | 6.10901 ms | 9.02382 ms | 32 | ✅ Pass |
| gemm_test_7.txt | 500 × 500 × 500 | 109.041 ms | 107.663 ms | 32 | ✅ Pass |
| gemm_test_8.txt | 700 × 300 × 600 | 97.3704 ms | 112.136 ms | 32 | ✅ Pass |

**Status = Pass** means, for that test file: (1) the program's own Simple and Blocking result
matrices were identical, and (2) both were independently cross-checked, element by element, against
a result matrix recomputed from the raw input file with a separate Python script (plain triple-loop
multiplication). All 8 test cases passed both checks.

Observed pattern: on this machine, Blocking GEMM was **not consistently faster** than Simple GEMM —
it was slower on 6 of the 8 test cases and only faster on 2 (tests 1 and 7). This is plausible for
`int`-typed dense matrices at these sizes on a modern x86 machine: the simple loop's working set
still mostly fits in cache, and the blocking version pays extra loop/boundary-check overhead without
a large enough cache-miss reduction to offset it. If the assignment expects Blocking to clearly
outperform Simple, it may be worth testing larger matrices (e.g. 1000×1000+) and/or sweeping the
block size (32/64/128) — the current fixed value of 32 has not been tuned.

Full result matrices for every test are written to `output/output_1.txt` … `output/output_8.txt`.

---

## CSR Conversion Result (Demo)

Using the demo file `input/input.txt` (assignment example graph, 5 vertices / 5 edges,
source = 0):

| Test File | Vertices | Edges | Result | Status |
|---|---:|---:|---|:---:|
| input.txt (demo) | 5 | 5 | Converted to CSR | ✅ Pass |

Actual console output produced by `./driver` with choice `2`:

```
Row Ptr :
0 2 4 7 9 10
COL_IDX :
1 2 0 3 0 3 4 1 2 2
```

This matches the `row_ptr` / `col_idx` arrays given in the assignment specification for this exact
example graph, confirming `readGraph()` and `buildCSR()` are correct for this case.

**Not yet covered:** the assignment requires graph test inputs at V = 10, 100, 10,000, 50,000, and
100,000 vertices, with E and graph type recorded in the README (Section 4.2 of the spec). Only the
single 5-vertex example above has been exercised — CSR conversion has not been tested at the
required larger scales because those graph files don't exist in this repo yet. Since CSR here only
feeds the buddy-task algorithms (BFS/DFS/SSSP), this table should be completed once those graph
input files exist.

---

## Correctness Verification

- **GEMM:** for every one of the 8 test files, the program's Simple and Blocking result matrices
  were compared and found identical. Each was also independently recomputed from the raw input file
  using a separate Python script and compared element-by-element against the program's output — all
  8 matched exactly.
- **CSR:** the demo graph's `row_ptr` / `col_idx` output was compared against the worked example in
  the assignment specification (Section 2.3) and matches exactly.

---

## Known Limitations / TODO before final submission

1. `input/input.txt` for CSR was missing from the original project — this was confirmed by actually
   running Choice 2 and getting `File not found!` before any changes were made. Only a spec-example
   demo file has been added since; replace it with the real graph(s) tied to the buddy-task inputs
   and re-test.
2. CSR has not been exercised at the required graph sizes (10 / 100 / 10,000 / 50,000 / 100,000
   vertices) — no test files at those sizes exist yet in this repo.
3. Blocking GEMM does not show a clear, consistent performance advantage over Simple GEMM at the
   current test sizes/block size (see note under GEMM Results) — worth investigating before claiming
   blocking is "faster" in any report or presentation.
4. `driver.exe` in the repo is a prebuilt Windows binary and was not re-verified in this pass — the
   numbers in this README come from a fresh build (`g++` command above) on Linux. Rebuild
   `driver.exe` from current source before distributing it, so it matches `src/`.

---

## Technologies Used

- C++17
- STL (`vector`, `ifstream`/`ofstream`, etc.)
- `std::chrono::high_resolution_clock` for timing
- g++
