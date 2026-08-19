#ifndef CSR_H
#define CSR_H

#include <vector>
#include "Graph.h"

using namespace std;

struct CSR
{
    int V;
    int E;

    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};

CSR convertToCSR(const Graph& graph);

#endif