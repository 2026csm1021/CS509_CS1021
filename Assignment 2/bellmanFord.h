#pragma once
#include <bits/stdc++.h>
#include"csr.h"
using namespace std;

vector<int> bellmanFord(
    const CSRGraph &csr, 
    int source, 
    bool &hasNegativeCycle
);