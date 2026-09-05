#include "Kruskal.h"
#include "DSU.h"

#include <algorithm>
#include <vector>

using namespace std;

MSTResult kruskalMST(const CSR& graph)
{
    int V = graph.V;

    vector<MSTEdge> edges;

    for (int u = 0; u < V; u++)
    {
        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];

        for (int i = start; i < end; i++)
        {
            int v = graph.col_idx[i];
            int w = graph.values[i];

            if (u < v)
            {
                edges.push_back({u, v, w});
            }
        }
    }

    sort(edges.begin(), edges.end(),
         [](const MSTEdge& a, const MSTEdge& b)
         {
             return a.weight < b.weight;
         });

    DSU dsu(V);

    vector<MSTEdge> mstEdges;
    int mstCost = 0;

    for (const MSTEdge& edge : edges)
    {
        if (dsu.find(edge.u) != dsu.find(edge.v))
        {
            mstEdges.push_back(edge);

            mstCost += edge.weight;

            dsu.unite(edge.u, edge.v);

            if ((int)mstEdges.size() == V - 1)
            {
                break;
            }
        }
    }

    bool connected = ((int)mstEdges.size() == V - 1);

    return {mstEdges, mstCost, connected};
}