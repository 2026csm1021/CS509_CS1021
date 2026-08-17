#ifndef GRAPH_H
#define GRAPH_H

#include<bits/stdc++.h>
using namespace std;

struct Edge {
    int neighbour;
    int weight;
};

struct Graph {
    int vertices;
    int Edges;

    vector<vector<Edge>> adjacency;
};

Graph readGraph(const string& filename);

#endif