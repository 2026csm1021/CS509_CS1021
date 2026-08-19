#ifndef GRAPH_H
#define GRAPH_H

#include <vector>
#include <utility>
#include <string>

using namespace std;

struct Graph
{
    int V;
    int E;

    vector<vector<pair<int, int>>> adj;
};

Graph readGraph(const string& filename);
void validateGraph(const Graph& graph);

#endif
