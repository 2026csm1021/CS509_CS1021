#include<bits/stdc++.h>
using namespace std;


struct CSRGraph
{
    int totalVertices;                      

    vector<int> row_ptr;        
    vector<int> col_idx;        
    vector<int> values;         
};


struct Graph
{
    int totalVertices;                     
    int totalEdges;                    
    vector<vector<int>> adjacencyList;    

    int sourceVertex;                 
};

Graph readGraph(string filename);

CSRGraph buildCSR(Graph graph);