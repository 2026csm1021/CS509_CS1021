#include "CSR.h"

using namespace std;

CSR convertToCSR(const Graph& graph)
{
    CSR csr;
    csr.V = graph.V;
    csr.E = graph.E;

    csr.row_ptr.resize(csr.V+1);

    csr.row_ptr[0] = 0;

    for(int u=0 ; u<csr.V; u++)
    {
        csr.row_ptr[u+1] = csr.row_ptr[u] + graph.adj[u].size(); 
    }

    csr.col_idx.resize(csr.row_ptr[csr.V]);

    for( int u=0 ; u<csr.V; u++){
        int start = csr.row_ptr[u];

        for(int j=0 ; j<(int)graph.adj[u].size(); j++)
        {
            csr.col_idx[start+j] = graph.adj[u][j];
        }
    } 
    return csr;   
}