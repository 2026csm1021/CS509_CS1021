#ifndef MSTTYPES_H
#define MSTTYPES_H

#include <vector>

using namespace std;

struct MSTEdge
{
    int u;
    int v;
    int weight;
};

struct MSTResult
{
    vector<MSTEdge> edges;
    int totalWeight;

    bool connected;
};

#endif
