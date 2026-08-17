#include<bits/stdc++.h>
#include"graph.h"

using namespace std;

int main(){
    Graph graph = readGraph("Input/mst_1.txt");

    cout<<"Vertices: "<<graph.vertices<<endl;
    cout<<"Edges: "<<graph.Edges<<endl;
    for(auto i=0; i<graph.vertices; i++){
        cout<<"Vertex "<<i<<":";
        for(auto e : graph.adjacency[i]){
            cout<<"("<<e.neighbour<<","<<e.weight<<")";
        }
        cout<<endl;
    }

    return 0;
}