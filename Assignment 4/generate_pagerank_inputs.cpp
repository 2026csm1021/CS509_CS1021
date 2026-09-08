#include <fstream>
#include <iostream>
#include <random>
#include <unordered_set>
#include <vector>

using namespace std;

long long edgeKey(int u, int v)
{
    return (static_cast<long long>(u) << 32) |
           static_cast<unsigned int>(v);
}

void generateGraph(int V, int E, const string& filename)
{
    vector<vector<int>> adj(V);
    unordered_set<long long> used;
    mt19937 rng(54321 + V);

    while (E > 0)
    {
        int u = rng() % V;
        int v = rng() % V;

        if (u == v)
            continue;

        if (used.insert(edgeKey(u, v)).second)
        {
            adj[u].push_back(v);
            E--;
        }
    }

    int actualE = 0;
    for (const auto& list : adj)
        actualE += list.size();

    ofstream file(filename);
    file << V << " " << actualE << '\n';

    for (int u = 0; u < V; u++)
    {
        file << u << " " << adj[u].size();

        for (int v : adj[u])
            file << " " << v;

        file << '\n';
    }

    file << "0.85\n";
    file << "0.000001\n";
    file << "100\n";
}

int main()
{
    generateGraph(10, 20, "input/pagerank_10.txt");
    generateGraph(100, 200, "input/pagerank_100.txt");
    generateGraph(1000, 2000, "input/pagerank_1000.txt");
    generateGraph(10000, 20000, "input/pagerank_10000.txt");
    generateGraph(50000, 100000, "input/pagerank_50000.txt");

    cout << "All PageRank inputs generated." << endl;
    return 0;
}
