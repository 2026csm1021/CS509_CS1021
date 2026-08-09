#include<bits/stdc++.h>
using namespace std;

struct CSRGraph
{
    int totalVertices;
    vector<int> rowPtr;
    vector<int> colIdx;
    vector<int> values;
};

struct Graph {
    int totalVertices;
    int totalEdges;
    vector<vector<pair<int,int>>>adjacencyList;
    int sourceVertex;
};

Graph readGraph(string filename);
CSRGraph buildcsrgraph(Graph graph );