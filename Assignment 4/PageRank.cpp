#include "PageRank.h"
#include <cmath>

using namespace std;

PageRankResult pageRank(
    const CSR& graph,
    double damping,
    double tolerance,
    int maxIterations
)
{
    int V = graph.V;

    PageRankResult result;

    result.rank.resize(V);

    result.iterations = 0;
    result.converged = false;

    vector<double> newRank(V);

    // Initial PageRank
    for (int i = 0; i < V; i++)
    {
        result.rank[i] = 1.0 / V;
    }

    // PageRank iterations
    for (int iteration = 0;
         iteration < maxIterations;
         iteration++)
    {
        // Random jump contribution
        for (int v = 0; v < V; v++)
        {
            newRank[v] = (1.0 - damping) / V;
        }

        // Distribute rank through outgoing edges
        for (int u = 0; u < V; u++)
        {
            int start = graph.row_ptr[u];
            int end = graph.row_ptr[u + 1];

            int outDegree = end - start;

            if (outDegree > 0)
            {
                double contribution =
                    result.rank[u] / outDegree;

                for (int i = start; i < end; i++)
                {
                    int v = graph.col_idx[i];

                    newRank[v] +=
                        damping * contribution;
                }
            }
            else
            {
                // Dangling vertex
                double contribution =
                    result.rank[u] / V;

                for (int v = 0; v < V; v++)
                {
                    newRank[v] +=
                        damping * contribution;
                }
            }
        }

        // Calculate total change
        double change = 0.0;

        for (int i = 0; i < V; i++)
        {
            change +=
                abs(newRank[i] - result.rank[i]);
        }

        // One iteration has completed
        result.iterations = iteration + 1;

        // Check convergence
        if (change <= tolerance)
        {
            result.rank = newRank;
            result.converged = true;

            break;
        }

        // Prepare for next iteration
        result.rank = newRank;
    }

    return result;
}