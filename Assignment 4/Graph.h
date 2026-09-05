#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <string>

using namespace std;

struct Graph
{
    int V;
    int E;

    vector<vector<int>> adj;

    // PageRank parameters
    double damping;
    double tolerance;
    int maxIterations;
};

Graph readGraph(const string& filename);
void validateGraph(const Graph& graph);

#endif