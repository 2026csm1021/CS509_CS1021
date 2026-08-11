#include "Floyd_Warshall.h"
#include <limits>

using namespace std;

vector<vector<int>> Floyd_Warshall(
    const vector<vector<int>>& graph,
    bool& hasNegativeCycle
)
{
    const int V = static_cast<int>(graph.size());
    const int INF = numeric_limits<int>::max();

    // Copy input matrix because Floyd-Warshall modifies distances
    vector<vector<int>> dist = graph;

    hasNegativeCycle = false;

    // Floyd-Warshall
    for (int k = 0; k < V; ++k)
    {
        for (int i = 0; i < V; ++i)
        {
            if (dist[i][k] == INF)
                continue;

            for (int j = 0; j < V; ++j)
            {
                if (dist[k][j] == INF)
                    continue;

                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] =
                        dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Negative cycle detection
    for (int i = 0; i < V; ++i)
    {
        if (dist[i][i] < 0)
        {
            hasNegativeCycle = true;
            break;
        }
    }

    return dist;
}