#include "Graph.h"

#include <fstream>
#include <stdexcept>
#include <string>
#include <vector>

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
        throw runtime_error("Invalid input file: V must be positive.");
    }

    if (graph.E < 0)
    {
        throw runtime_error("Invalid input file: E cannot be negative.");
    }

    graph.adj.resize(graph.V);
    vector<bool> seen(graph.V, false);

    for (int i = 0; i < graph.V; i++)
    {
        int u;
        int degree;

        if (!(file >> u >> degree))
        {
            throw runtime_error(
                "Invalid input file: could not read vertex id and degree."
            );
        }

        if (u < 0 || u >= graph.V)
        {
            throw runtime_error(
                "Invalid input file: vertex id out of range."
            );
        }

        if (seen[u])
        {
            throw runtime_error(
                "Invalid input file: duplicate vertex id."
            );
        }
        seen[u] = true;

        if (degree < 0)
        {
            throw runtime_error(
                "Invalid input file: degree cannot be negative."
            );
        }

        graph.adj[u].reserve(degree);

        for (int j = 0; j < degree; j++)
        {
            int v;

            if (!(file >> v))
            {
                throw runtime_error(
                    "Invalid input file: missing neighbour id."
                );
            }

            if (v < 0 || v >= graph.V)
            {
                throw runtime_error(
                    "Invalid input file: neighbour id out of range."
                );
            }

            graph.adj[u].push_back(v);
        }
    }

    // PageRank parameters are present only for PageRank input files.
    if (file >> graph.damping >> graph.tolerance >> graph.maxIterations)
    {
        graph.hasPageRankParameters = true;
    }

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

void validateVertexColoringGraph(const Graph& graph)
{
    validateGraph(graph);

    long long degreeSum = 0;

    for (int u = 0; u < graph.V; u++)
    {
        degreeSum += graph.adj[u].size();

        for (int i = 0; i < (int)graph.adj[u].size(); i++)
        {
            for (int j = i + 1; j < (int)graph.adj[u].size(); j++)
            {
                if (graph.adj[u][i] == graph.adj[u][j])
                {
                    throw runtime_error(
                        "Invalid graph: duplicate edge in adjacency list."
                    );
                }
            }
        }
    }

    if (degreeSum != 2LL * graph.E)
    {
        throw runtime_error(
            "Invalid graph: adjacency entries do not match 2E for an undirected graph."
        );
    }

    for (int u = 0; u < graph.V; u++)
    {
        for (int v : graph.adj[u])
        {
            bool found = false;

            for (int x : graph.adj[v])
            {
                if (x == u)
                {
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                throw runtime_error(
                    "Invalid graph: undirected edge is missing from the other endpoint."
                );
            }
        }
    }
}

void validatePageRankGraph(const Graph& graph)
{
    validateGraph(graph);

    long long edgeCount = 0;

    for (int u = 0; u < graph.V; u++)
    {
        edgeCount += graph.adj[u].size();
    }

    if (edgeCount != graph.E)
    {
        throw runtime_error(
            "Invalid graph: adjacency entries do not match E for a directed graph."
        );
    }

    if (!graph.hasPageRankParameters)
    {
        throw runtime_error(
            "Invalid PageRank input: DAMPING, TOLERANCE and MAX_ITERATIONS are required."
        );
    }

    if (graph.damping <= 0.0 || graph.damping >= 1.0)
    {
        throw runtime_error(
            "Invalid PageRank input: DAMPING must be between 0 and 1."
        );
    }

    if (graph.tolerance <= 0.0)
    {
        throw runtime_error(
            "Invalid PageRank input: TOLERANCE must be positive."
        );
    }

    if (graph.maxIterations <= 0)
    {
        throw runtime_error(
            "Invalid PageRank input: MAX_ITERATIONS must be positive."
        );
    }
}
