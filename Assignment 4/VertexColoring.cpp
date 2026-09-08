#include "VertexColoring.h"

#include <algorithm>
#include <vector>

using namespace std;

vector<int> vertexColoring(const CSR& graph)
{
    int V = graph.V;
    vector<int> degree(V);

    for (int u = 0; u < V; u++)
    {
        degree[u] = graph.row_ptr[u + 1] - graph.row_ptr[u];
    }

    vector<int> order(V);
    for (int i = 0; i < V; i++)
    {
        order[i] = i;
    }

    // Welsh-Powell ordering: non-increasing degree.
    sort(order.begin(), order.end(),
         [&](int a, int b)
         {
             if (degree[a] != degree[b])
                 return degree[a] > degree[b];
             return a < b;
         });

    vector<int> color(V, 0);
    vector<int> used(V + 1, 0);
    int mark = 0;

    // Greedy coloring in Welsh-Powell order.
    for (int k = 0; k < V; k++)
    {
        int u = order[k];
        mark++;

        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];

        for (int i = start; i < end; i++)
        {
            int v = graph.col_idx[i];

            if (color[v] != 0)
                used[color[v]] = mark;
        }

        int c = 1;
        while (used[c] == mark)
            c++;

        color[u] = c;
    }

    return color;
}
