#ifndef GRAPH_H
#define GRAPH_H

#include <string>
#include <vector>

using namespace std;

struct Graph
{
    int V = 0;
    int E = 0;
    vector<vector<int>> adj;

    double damping = 0.0;
    double tolerance = 0.0;
    int maxIterations = 0;
    bool hasPageRankParameters = false;
};

Graph readGraph(const string& filename);
void validateGraph(const Graph& graph);
void validateVertexColoringGraph(const Graph& graph);
void validatePageRankGraph(const Graph& graph);

#endif
