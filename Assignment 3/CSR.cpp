#include "CSR.h"
#include "Graph.h"

using namespace std;

CSR convertToCSR(const Graph& graph)
{
    CSR csr;

    csr.V = graph.V;
    csr.E = graph.E;
    csr.row_ptr.resize(csr.V + 1);

    csr.row_ptr[0] = 0;

    for (int u = 0; u < csr.V; u++)
    {
        csr.row_ptr[u + 1] =
            csr.row_ptr[u] + graph.adj[u].size();
    }

    int totalEntries = csr.row_ptr[csr.V];

    csr.col_idx.resize(totalEntries);
    csr.values.resize(totalEntries);

    int index = 0;

    for (int u = 0; u < csr.V; u++)
    {
        for (const auto& edge : graph.adj[u])
        {
            int v = edge.first;
            int w = edge.second;

            csr.col_idx[index] = v;
            csr.values[index] = w;

            index++;
        }
    }

    return csr;
}