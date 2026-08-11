#include "bellmanFord.h"
#include <limits>

using namespace std;

vector<int> bellmanFord(const CSRGraph &csr, int source, bool &hasNegativeCycle)
{
    const int INF = numeric_limits<int>::max();

    vector<int> dist(csr.Vertices, INF);

    dist[source] = 0;

    for (int i = 0; i < csr.Vertices - 1; i++)
    {
        for (int u = 0; u < csr.Vertices; u++)
        {
            if (dist[u] == INF)
                continue;

            for (int j = csr.row_ptr[u];
                 j < csr.row_ptr[u + 1];
                 j++)
            {
                int v = csr.col_idx[j];
                int weight = csr.values[j];

                if (dist[u] + weight < dist[v]){
                    dist[v] = dist[u] + weight;
                }
            }
        }
    }

    hasNegativeCycle = false;
    for (int u = 0; u < csr.Vertices; u++)
    {
        if (dist[u] == INF)
            continue;

        for (int j = csr.row_ptr[u]; j < csr.row_ptr[u + 1]; j++)
        {
            int v = csr.col_idx[j];
            int weight = csr.values[j];

            if (dist[u] + weight < dist[v])
            {
                hasNegativeCycle = true;
                break;
            }
        }
        if (hasNegativeCycle)
            break;
    }

    return dist;
}