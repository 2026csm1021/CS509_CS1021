#include "DSU.h"

DSU::DSU(int n)
{
    // Initially every vertex is its own parent
    parent.resize(n);

    // Initially all ranks are 0
    rank.resize(n, 0);

    for (int i = 0; i < n; i++)
    {
        parent[i] = i;
    }
}

int DSU::find(int x)
{
    // x is the representative of its own set
    if (parent[x] == x)
    {
        return x;
    }

    // Path compression
    parent[x] = find(parent[x]);

    return parent[x];
}

void DSU::unite(int x, int y)
{
    
    x = find(x);
    y = find(y);

    if (x == y)
    {
        return;
    }

    if (rank[x] < rank[y])
    {
        parent[x] = y;
    }
    else if (rank[x] > rank[y])
    {
        parent[y] = x;
    }
    else
    {
        parent[y] = x;
        rank[x]++;
    }
}
