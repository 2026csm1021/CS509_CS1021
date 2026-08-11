#pragma once

#include <bits/stdc++.h>
using namespace std;

struct Graph
{
    int totalVertices;
    int totalEdges;
    vector<vector<pair<int,int>>> adjacencyList;
    int sourceVertex;
};

Graph readGraph(const string& filename);