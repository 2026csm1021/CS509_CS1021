#ifndef PAGERANK_H
#define PAGERANK_H

#include <vector>
#include "CSR.h"

using namespace std;

struct PageRankResult
{
    vector<double> rank;
    int iterations;
    bool converged;
};

PageRankResult pageRank(
    const CSR& graph,
    double damping,
    double tolerance,
    int maxIterations
);

#endif