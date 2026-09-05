#include "Graph.h"
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

Graph readGraph(const string& filename)
{
    Graph graph;

    ifstream file(filename);

    if (!file)
    {
        throw runtime_error(
            "Could not open input file: " + filename
        );
    }

    // Read number of vertices and edges
    file >> graph.V >> graph.E;

    graph.adj.resize(graph.V);

    // Read adjacency list
    for (int i = 0; i < graph.V; i++)
    {
        int u;
        int degree;

        file >> u >> degree;

        for (int j = 0; j < degree; j++)
        {
            int v;

            file >> v;

            graph.adj[u].push_back(v);
        }
    }

    // Read PageRank parameters
    if (file >> graph.damping)
    {
        file >> graph.tolerance;
        file >> graph.maxIterations;
    }

    file.close();

    return graph;
}

void validateGraph(const Graph& graph)
{
    if (graph.V <= 0)
    {
        throw runtime_error(
            "Invalid graph: V must be positive."
        );
    }

    if ((int)graph.adj.size() != graph.V)
    {
        throw runtime_error(
            "Invalid graph: adjacency list size does not match V."
        );
    }

    for (int u = 0; u < graph.V; u++)
    {
        for (int v : graph.adj[u])
        {
            if (v < 0 || v >= graph.V)
            {
                throw runtime_error(
                    "Invalid graph: neighbour id out of range."
                );
            }

            if (v == u)
            {
                throw runtime_error(
                    "Invalid graph: self-loop detected."
                );
            }
        }
    }
}