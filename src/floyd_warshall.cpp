#include<bits/stdc++.h>
#include"floyd_warshall.h"

using namespace std;

vector<vector<int>> floydwarshall(const CSRGraph &csr)
{
    const int INF = numeric_limits<int>::max();
    int V = csr.totalVertices;
    vector<vector<int>> dist( V, vector<int>(V, INF));

    for(int i=0; i<V; i++){
        dist[i][i]=0;
    }
    for(int u=0; u<V; u++){
        for(int j=csr.rowPtr[u]; j<csr.rowPtr[u+1]; j++){
            int v = csr.colIdx[j];
            int weight = csr.values[j];
            dist[u][v] = weight;
        }
    }
    for(int k=0; k<V; k++){
        for(int i=0; i<V; i++){
            if(dist[i][k] == INF)
            continue;
            for(int j=0; j<V; j++){
                if(dist[k][j] == INF)
                continue;
                if(dist[i][k]+dist[k][j]<dist[i][j]){
                    dist[i][j] = dist[i][k]+dist[k][j];
                }
            }
        }
        
    }
    return dist;
}
