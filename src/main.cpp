#include <bits/stdc++.h>
#include "gemm.h"

using namespace std;

void SimpleGEMM()
{
    int blockSize = 32;

    for (int test = 1; test <=8; test++){
        string inputFile = "input/gemm_test_" + to_string(test) + ".txt";
        string outputFile = "output/simple_Matrix_output" + to_string(test) + ".txt";
        ifstream fin(inputFile);
        if (!fin){
            cout<<inputFile<<" Not Found"<<endl;
            continue;
        }

        int M, K, N;
        fin >> M >> K >> N;

        vector<vector<int>> A(M, vector<int>(K));
        vector<vector<int>> B(K, vector<int>(N));

        for (int i = 0; i < M; i++){
            for (int j = 0; j < K; j++){
                fin >> A[i][j];
            }
        }

        for (int i = 0; i < K; i++){
            for (int j = 0; j < N; j++){
                
            }
        }

        fin.close();

        auto start = chrono::high_resolution_clock::now();

        vector<vector<int>> simpleResult = simpleMatrix(A, B, M, K, N);

        auto end = chrono::high_resolution_clock::now();

        double simpleTime = chrono::duration<double, milli>(end - start).count();

        ofstream fout(outputFile);
        fout << "Simple GEMM Result " << endl;

        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++){
                fout << simpleResult[i][j] << " ";
            }
            fout<<endl;
        }

        fout<<endl;
        fout << "Execution Time: "<< simpleTime << " ms"<<endl;

    cout << "All Test Cases Completed Successfully!"<<endl;
    }
    return ;
}

void BlockingGEMM() {
    int blockSize = 32;
    
    for(int test=1; test<=8; test++){
        string inputFile = "input/gemm_test_" + to_string(test) + ".txt";
        string outputFile = "output/blocking_Matrix_output_"+ to_string(test) +".txt";

        ifstream fin(inputFile);
        if(!fin){
            cout<<"File Not Found..."<<endl;
            continue;
        }

        int M, K, N;
        fin>>M>>K>>N;

        vector<vector<int>> A (M, vector<int>(K));
        vector<vector<int>> B (K, vector<int>(N));

        for(int i=0; i<M; i++){
            for(int j=0; j<K; j++){
                fin>>A[i][j];
            }
        }

        for(int i=0; i<K; i++){
            for(int j=0; j<N; j++){
                fin>>B[i][j];
            }
        }

        fin.close();
        
        auto start = chrono::high_resolution_clock::now();

        vector<vector<int>> blockResult = blockingMatrix(A, B, M, K, N, blockSize);

        auto end = chrono::high_resolution_clock::now();

        double blockTime = chrono::duration<double, milli>(end - start).count();

        ofstream fout(outputFile);

        fout << "BlockingGEMM Result" << endl;

        for (int i = 0; i < M; i++){
            for (int j = 0; j < N; j++){
                fout<<blockResult[i][j]<< " ";
            }    
            fout <<endl;
        }
        fout << "Execution Time: "<< blockTime << " ms" << endl;

        fout.close();
        cout << "BlockingGEMM Test Case " << test << " Completed" << endl;
    }
}