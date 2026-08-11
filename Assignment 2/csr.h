#pragma once
#include<bits/stdc++.h>
#include "graph.h"

using namespace std;

struct CSRGraph
{
    int Vertices;
    vector<int> row_ptr;
    vector<int> col_idx;
    vector<int> values;
};

CSRGraph CSR(const Graph& G );