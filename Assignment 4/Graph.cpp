#include<iostream>
#include<stdexcept>
#include<fstream>
#include<string>
#include<vector>
#include"Graph.h"

using namespace std;

Graph readGraph(const string& filename)
{
    Graph graph;
    ifstream file(filename);

    if(!file)
    {
        throw runtime_error("Could not open file :" + filename);
    }

    file>> graph.V>>graph.E;
    graph.adj.resize(graph.V);

    for(int i-0; i<graph.V; i++)
    {
        int u , degree;
        file>>u>>degree;
        for(int j=0; j<degree; j++){
            int v;
            file>>v;
            graph.adj[u].push_back(v);
        }
    }
    file.close( );

    return graph;

}

void validateGraph(const Graph& graph)
{
    if(graph.V <=0)
    {
        throw runtime_error("Invalid graph : V must be positive.");
    }
    if((int) graph.adj.size() != graph.V)
    {
        throw runtime_error("Invalid graph: adjacency list size does not match V.");
    }

    for(int u=0; u<graph.V; u++)
    {
        for(int v : graph.adj[u])
        {
            if(v<0 || v>=graph.V)
            {
                throw runtime_error("Invalid graph : neighbour id out of range.");
            }
            if(v==u)
            {
                throw runtime_error("Invlaid graph : self_loop detected.");
            }
       }
    }
}