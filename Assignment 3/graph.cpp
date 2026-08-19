#include "Graph.h"
#include <fstream>
#include <iostream>
#include <queue>
#include <algorithm>

using namespace std;

Graph readGraph(const string& filename)
{
    Graph graph;

    ifstream file(filename);

    if (!file)
    {
        throw runtime_error("Could not open input file: " + filename);
    }

    if (!(file >> graph.V >> graph.E))
    {
        throw runtime_error("Invalid input file: could not read V and E.");
    }

    if (graph.V <= 0)
    {
        throw runtime_error("Invalid input file: V must be a positive integer.");
    }

    graph.adj.resize(graph.V);

    for (int i = 0; i < graph.V; i++)
    {
        int u;
        int degree;

        if (!(file >> u >> degree))
        {
            throw runtime_error("Invalid input file: could not read vertex id/degree for line " + to_string(i));
        }

        if (u < 0 || u >= graph.V)
        {
            throw runtime_error("Invalid input file: vertex id " + to_string(u) + " is out of range [0, " + to_string(graph.V) + ").");
        }

        if (degree < 0)
        {
            throw runtime_error("Invalid input file: negative degree for vertex " + to_string(u));
        }

        for (int j = 0; j < degree; j++)
        {
            int v;
            int w;

            if (!(file >> v >> w))
            {
                throw runtime_error("Invalid input file: could not read neighbour/weight for vertex " + to_string(u));
            }

            if (v < 0 || v >= graph.V)
            {
                throw runtime_error("Invalid input file: neighbour id " + to_string(v) + " for vertex " + to_string(u) + " is out of range.");
            }

            graph.adj[u].push_back({v, w});
        }
    }

    file.close();

    return graph;
}

void validateGraph(const Graph& graph)
{
    if (graph.V <= 0)
    {
        throw runtime_error("Invalid graph: V must be positive.");
    }

    if ((int)graph.adj.size() != graph.V)
    {
        throw runtime_error("Invalid graph: adjacency list size does not match V.");
    }

    for (int u = 0; u < graph.V; u++)
    {
        for (const auto& e : graph.adj[u])
        {
            int v = e.first;

            if (v < 0 || v >= graph.V)
            {
                throw runtime_error("Invalid graph: neighbour id out of range at vertex " + to_string(u));
            }

            if (v == u)
            {
                throw runtime_error("Invalid graph: self-loop detected at vertex " + to_string(u));
            }
        }
    }

    vector<vector<pair<int, int>>> sortedAdj(graph.V);

    for (int u = 0; u < graph.V; u++)
    {
        sortedAdj[u] = graph.adj[u];
        sort(sortedAdj[u].begin(), sortedAdj[u].end());
    }

    for (int u = 0; u < graph.V; u++)
    {
        for (const auto& e : graph.adj[u])
        {
            int v = e.first;
            int w = e.second;

            bool found = binary_search(sortedAdj[v].begin(), sortedAdj[v].end(), make_pair(u, w));

            if (!found)
            {
                throw runtime_error("Invalid graph: undirected edge (" + to_string(u) + ", " + to_string(v) +
                                     ") is missing or has a mismatched weight in vertex " + to_string(v) + "'s adjacency list.");
            }
        }
    }

    vector<bool> visited(graph.V, false);
    queue<int> q;

    q.push(0);
    visited[0] = true;
    int visitedCount = 1;

    while (!q.empty())
    {
        int u = q.front();
        q.pop();

        for (const auto& e : graph.adj[u])
        {
            int v = e.first;

            if (!visited[v])
            {
                visited[v] = true;
                visitedCount++;
                q.push(v);
            }
        }
    }

    if (visitedCount != graph.V)
    {
        throw runtime_error("Invalid graph: graph is not connected (" + to_string(visitedCount) +
                             " of " + to_string(graph.V) + " vertices reachable from vertex 0).");
    }
}
