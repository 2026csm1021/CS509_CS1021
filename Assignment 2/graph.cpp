#include "graph.h"
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

Graph readGraph(const string& filename)
{
    Graph G;

    ifstream input(filename);

    if (!input.is_open())
    {
        cerr << "Error: Cannot open file "
             << filename << endl;

        return G;
    }


    input >> G.totalVertices;
    input >> G.totalEdges;

    G.adjacencyList.resize(G.totalVertices);


    for (int i = 0; i < G.totalVertices; ++i)
    {
        int u;
        int numberOfEdges;

        input >> u >> numberOfEdges;

        for (int j = 0; j < numberOfEdges; ++j)
        {
            int v;
            int weight;

            input >> v >> weight;

            G.adjacencyList[u].push_back(
                {v, weight}
            );
        }
    }

    string sourceWord;

    input >> sourceWord;
    input >> G.sourceVertex;

    input.close();

    return G;
}