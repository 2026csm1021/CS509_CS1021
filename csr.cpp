#include "csr.h"

CSRGraph CSR(const Graph& G)
{
    CSRGraph csr;

    const int V = G.totalVertices;

    csr.Vertices = V;

    // CSR row pointer: V + 1 elements
    csr.row_ptr.resize(V + 1);

    // Build row_ptr
    csr.row_ptr[0] = 0;

    for (int u = 0; u < V; ++u)
    {
        csr.row_ptr[u + 1] =
            csr.row_ptr[u] +
            static_cast<int>(G.adjacencyList[u].size());
    }

    // Total number of edges
    const int E = csr.row_ptr[V];

    csr.col_idx.resize(E);
    csr.values.resize(E);

    // Fill column indices and edge weights
    int index = 0;

    for (int u = 0; u < V; ++u)
    {
        for (const auto& edge : G.adjacencyList[u])
        {
            csr.col_idx[index] = edge.first;
            csr.values[index] = edge.second;
            ++index;
        }
    }

    return csr;
}