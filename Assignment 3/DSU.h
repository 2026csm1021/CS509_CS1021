#ifndef DSU_H
#define DSU_H

#include <vector>

using namespace std;

class DSU
{
private:
    vector<int> parent;
    vector<int> rank;

public:

    DSU(int n);

    int find(int x);

    void unite(int x, int y);
};

#endif