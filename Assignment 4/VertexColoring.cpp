#include "VertexColoring.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<int> vertexColoring(const CSR& graph)
{
    int V = graph.V;

    vector<int> degree(V);

    // Calculate degree of every vertex
    for (int u = 0; u < V; u++)
    {
        degree[u] =
            graph.row_ptr[u + 1] -
            graph.row_ptr[u];
    }

    // Create vertex order
    vector<int> order(V);

    for (int i = 0; i < V; i++)
    {
        order[i] = i;
    }

    // Welsh-Powell ordering
    // Higher degree first
    for (int i = 0; i < V - 1; i++)
    {
        for (int j = i + 1; j < V; j++)
        {
            if (degree[order[i]] < degree[order[j]])
            {
                swap(order[i], order[j]);
            }
        }
    }

    // 0 means not colored
    vector<int> color(V, 0);

    // Greedy coloring
    for (int k = 0; k < V; k++)
    {
        int u = order[k];

        vector<bool> used(V + 1, false);

        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];

        // Check colors of neighbours
        for (int i = start; i < end; i++)
        {
            int v = graph.col_idx[i];

            if (color[v] != 0)
            {
                used[color[v]] = true;
            }
        }

        // Find smallest available color
        int c = 1;

        while (used[c])
        {
            c++;
        }

        color[u] = c;
    }

    return color;
}