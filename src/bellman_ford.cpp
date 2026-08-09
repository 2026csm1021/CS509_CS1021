#include "bellman_ford.h"
#include <limits>

using namespace std;

vector<int> bellmanFord(const CSRGraph &csr, int source)
{
    const int INF = numeric_limits<int>::max();

    vector<int> dist(csr.totalVertices, INF);

    dist[source] = 0;

    for (int i = 0; i < csr.totalVertices - 1; i++)
    {
        for (int u = 0; u < csr.totalVertices; u++)
        {
            if (dist[u] == INF)
                continue;

            for (int j = csr.rowPtr[u];
                 j < csr.rowPtr[u + 1];
                 j++)
            {
                int v = csr.colIdx[j];
                int weight = csr.values[j];

                if (dist[u] + weight < dist[v]){
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }
    
    return dist;
}