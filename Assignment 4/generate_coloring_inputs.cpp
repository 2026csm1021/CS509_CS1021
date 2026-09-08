#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

long long edgeKey(int u, int v)
{
    if (u > v)
        swap(u, v);

    return (static_cast<long long>(u) << 32) |
           static_cast<unsigned int>(v);
}

void generateGraph(int V, int E, const string& filename)
{
    vector<pair<int, int>> edges;
    unordered_set<long long> used;
    mt19937 rng(12345 + V);

    // Ring guarantees that every vertex is present and the graph is connected.
    for (int u = 0; u < V; u++)
    {
        int v = (u + 1) % V;
        edges.push_back({u, v});
        used.insert(edgeKey(u, v));
    }

    while ((int)edges.size() < E)
    {
        int u = rng() % V;
        int v = rng() % V;

        if (u == v)
            continue;

        long long key = edgeKey(u, v);

        if (used.insert(key).second)
            edges.push_back({u, v});
    }

    vector<vector<int>> adj(V);

    for (auto [u, v] : edges)
    {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    ofstream file(filename);

    file << V << " " << E << '\n';

    for (int u = 0; u < V; u++)
    {
        file << u << " " << adj[u].size();

        for (int v : adj[u])
            file << " " << v;

        file << '\n';
    }
}

int main()
{
    generateGraph(10, 10, "input/coloring_10.txt");
    generateGraph(100, 200, "input/coloring_100.txt");
    generateGraph(1000, 2000, "input/coloring_1000.txt");
    generateGraph(10000, 20000, "input/coloring_10000.txt");
    generateGraph(50000, 100000, "input/coloring_50000.txt");
    generateGraph(100000, 200000, "input/coloring_100000.txt");

    cout << "All valid Vertex Coloring inputs generated." << endl;
    return 0;
}
