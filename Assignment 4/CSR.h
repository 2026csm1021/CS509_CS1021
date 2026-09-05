#ifndef CSR_H
#define CSR_H


#include "Graph.h"
#include<vector>
using namespace std;

struct CSR{
    int V;
    int E;

    vector<int> row_ptr;
    vector<int> col_idx;
};

CSR convertToCSR(const Graph& graph);

#endif