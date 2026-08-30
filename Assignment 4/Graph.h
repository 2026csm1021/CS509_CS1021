#ifndef GRAPH_H
#define GRAPH_H
#include<string>
#include<vector>

using namespace std;

struct Graph {
    int V;
    int E;

    vector<vector<int>> adj;
};

Graph readGraph(const string& filename);
void validateGraph(const Graph& graph);

#endif