#include<bits/stdc++.h>
#include"csr.h"

using namespace std;

Graph readGraph(string fileName)
{
    Graph graph;
    ifstream file(fileName);

    if (!file)
    {
        cout << "File not found!" << endl;
        exit(1);
    }

    file >> graph.totalVertices >> graph.totalEdges;

    graph.adjacencyList.resize(graph.totalVertices);

    for (int i = 0; i < graph.totalVertices; i++)
    {
        int vertex, neighbours;
        file >> vertex >> neighbours;

        while (neighbours--)
        {
            int neighbour;
            file >> neighbour;
            // Assignment 1's graph input is unweighted.  Store a unit value
            // so it matches the weighted adjacency-list type in csr.h.
            graph.adjacencyList[vertex].push_back({neighbour, 1});
        }
    }

    string temp;
    file >> temp >> graph.sourceVertex;

    return graph;
}


CSRGraph buildCSR(Graph graph)
{
    CSRGraph csr;

    csr.totalVertices = graph.totalVertices;
    csr.row_ptr.push_back(0);

    for (int i = 0; i < graph.totalVertices; i++)
    {
        for (const auto& [neighbour, value] : graph.adjacencyList[i])
        {
            csr.col_idx.push_back(neighbour);
            csr.values.push_back(value);
        }

        csr.row_ptr.push_back(csr.col_idx.size());
    }

    return csr;
}
