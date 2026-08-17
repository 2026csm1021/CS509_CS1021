#include<bits/stdc++.h>
#include"graph.h"

Graph readGraph(const string& filename){
    fstream file(filename);
    if(!file){
        cout<<"Invalid file";
        return Graph();
    }

    Graph graph;
    //Read # of vertices and edges
    file>>graph.vertices>>graph.Edges;  
    //create adjacency list for vertices
    graph.adjacency.resize(graph.vertices);

    for(int i=0; i<graph.vertices; i++){
        int curr_vertex , degree;
        file>>curr_vertex>>degree;
        for(int j=0; j<degree; j++){
            int neighbour, weight;
            file>>neighbour>>weight;

            Edge e;
            e.neighbour = neighbour;
            e.weight    = weight;

            graph.adjacency[curr_vertex].push_back(e);
        }
    }
    return graph;

}