#include<bits/stdc++.h>
using namespace std;

vector<vector<int>> simpleMatrix(
    vector<vector<int>>& matrixA,
    vector<vector<int>>& matrixB,
    int M, // M=row of matrixA
    int K,  // K = column of matrixA = row of matrixB
    int N // N=column of matrixB
);

vector<vector<int>> blockingMatrix(
    vector<vector<int>>& A,
    vector<vector<int>>& B,
    int M, // M=row of matrixA
    int K,  // K = column of matrixA = row of matrixB
    int N, // N=column of matrixB
    
    int blockSize // Size of each block
);

void SimpleGEMM();
void BlockingGEMM();
