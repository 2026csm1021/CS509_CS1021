#include<bits/stdc++.h>
#include"gemm.h"
#include"csr.h"

using namespace std;

int main(){
    int choice;
    cout<<"   CS509 Assignment 1\n";
    cout << "1. GEMM "<<endl;
    cout << "2. CSR "<<endl;

    cout<<" Enter Choice: ";
    cin>>choice;

    switch(choice){
        case 1:{
            int op;
            cout << "1. Simple Matrix Multiplication" << endl;
            cout << "2. Blocking Matrix Multiplication" << endl;

            cout << "Enter Choice : ";
            cin >> op;

            if (op == 1)
            {
                SimpleGEMM();
            }
            else if (op == 2)
            {
                BlockingGEMM();
            }
            else
            {
                cout << "Invalid Choice!" << endl;
            }

            break;
        }
        case 2:{
            cout<<"Calling CSR Graph Function here."<<endl;
            Graph graph = readGraph("input/input.txt");
            CSRGraph csr = buildCSR(graph);

            cout<<"Row Ptr :"<<endl;
            for(int x : csr.row_ptr)
                cout<< x <<" "<<endl;

            cout<<"COL_IDX :"<<endl;
            for(int x : csr.col_idx)
                cout<< x <<" "<<endl;
            
            if(!csr.values.empty()){
                cout<<"Values : ";
                for(int x : csr.values)
                    cout<< x <<" ";
            }
            cout<<endl;
            break;
        }
        case 0:
        {
            cout << "Program Closed." << endl;
            break;
        }
        default:
            cout<<"Invalid Choice.. "<<endl;

    }

    return 0;
}