#include<bits/stdc++.h>
#include "gemm.h"
using namespace std;
vector<vector<int>> simpleMatrix(vector<vector<int>>&A, vector<vector<int>>&B, int M , int K, int N)
{
    vector<vector<int>> result(M, vector<int>(N,0));
    for (int i = 0; i < M; i++)
        for (int j = 0; j < N; j++)
            for (int k = 0; k < K; k++)
                result[i][j] += A[i][k] * B[k][j];

    return result;
}

vector<vector<int>> blockingMatrix(vector<vector<int>>& A, vector<vector<int>>& B,
                                 int M, int K, int N, int blockSize)
{
    vector<vector<int>> result(M, vector<int>(N, 0));

    for (int row = 0; row < M; row += blockSize)
        for (int col = 0; col < N; col += blockSize)
            for (int kStart = 0; kStart < K; kStart += blockSize)
            {
                int rowEnd = min(row + blockSize, M);
                int colEnd = min(col + blockSize, N);
                int kEnd = min(kStart + blockSize, K);

                for (int i = row; i < rowEnd; i++)
                    for (int j = col; j < colEnd; j++)
                        for (int k = kStart; k < kEnd; k++)
                            result[i][j] += A[i][k] * B[k][j];
            }

    return result;
}