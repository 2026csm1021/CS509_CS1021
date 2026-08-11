#pragma once
#include <vector>

using namespace std;

vector<vector<int>> Floyd_Warshall(
    const vector<vector<int>>& graph,
    bool& hasNegativeCycle
);