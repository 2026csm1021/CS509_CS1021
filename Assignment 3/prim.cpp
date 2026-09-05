#include "Prim.h"
#include <queue>
#include <tuple>
#include <vector>


using namespace std;

MSTResult primMST(const CSR& graph)
{
    int V = graph.V;

    vector<bool> inMST(V, false);

    priority_queue<
        tuple<int, int, int>,
        vector<tuple<int, int, int>>,
        greater<tuple<int, int, int>>
    > pq;

    vector<MSTEdge> mstEdges;

    int mstCost = 0;

    pq.push({0, 0, -1});

    while (!pq.empty())
    {
        auto [wt, u, parent] = pq.top();
        pq.pop();

        if (inMST[u])
        {
            continue;
        }

        inMST[u] = true;
        mstCost += wt;

        if (parent != -1)
        {
            mstEdges.push_back({parent, u, wt});
        }

        int start = graph.row_ptr[u];
        int end = graph.row_ptr[u + 1];

        for (int i = start; i < end; i++)
        {
            int v = graph.col_idx[i];
            int w = graph.values[i];

            if (!inMST[v])
            {
                pq.push({w, v, u});
            }
        }
    }

    bool connected = ((int)mstEdges.size() == V - 1);

    return {mstEdges, mstCost, connected};
}