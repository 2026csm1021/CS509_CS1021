#include <bits/stdc++.h>
#include <chrono>
#include <filesystem>

#include "graph.h"
#include "csr.h"
#include "bellmanFord.h"
#include "Floyd_Warshall.h"

using namespace std;
using namespace std::chrono;

namespace fs = std::filesystem;

const int INF = numeric_limits<int>::max();


// ============================================================
// Read Floyd-Warshall input file
// ============================================================

vector<vector<int>> readFloydInput(const string& filename)
{
    ifstream input(filename);

    if (!input.is_open())
    {
        throw runtime_error(
            "Cannot open file: " + filename
        );
    }

    int V;
    input >> V;

    vector<vector<int>> graph(
        V,
        vector<int>(V, INF)
    );

    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            string value;
            input >> value;

            if (value == "INF" || value == "inf")
            {
                graph[i][j] = INF;
            }
            else
            {
                graph[i][j] = stoi(value);
            }
        }
    }

    input.close();

    return graph;
}


// ============================================================
// Write Bellman-Ford output
// ============================================================

void writeBellmanOutput(
    const string& outputFile,
    const string& inputFile,
    const Graph& graph,
    const vector<int>& dist,
    bool negativeCycle,
    double timeMs)
{
    ofstream output(outputFile);

    if (!output.is_open())
    {
        throw runtime_error(
            "Cannot create output file: " + outputFile
        );
    }

    output << "========================================\n";
    output << "          BELLMAN-FORD RESULTS\n";
    output << "========================================\n\n";

    output << "Input File: " << inputFile << "\n";
    output << "Vertices: " << graph.totalVertices << "\n";
    output << "Edges: " << graph.totalEdges << "\n";
    output << "Source: " << graph.sourceVertex << "\n\n";

    output << "Negative Cycle: "
           << (negativeCycle ? "Yes" : "No")
           << "\n\n";

    if (!negativeCycle)
    {
        output << "Vertex\tDistance\n";
        output << "-------------------\n";

        for (int v = 0;
             v < graph.totalVertices;
             ++v)
        {
            output << v << "\t";

            if (dist[v] == INF)
                output << "INF";
            else
                output << dist[v];

            output << "\n";
        }
    }

    output << "\nExecution Time: "
           << fixed << setprecision(6)
           << timeMs << " ms\n";

    output.close();
}


// ============================================================
// Write Floyd-Warshall output
// ============================================================

void writeFloydOutput(
    const string& outputFile,
    const string& inputFile,
    const vector<vector<int>>& dist,
    bool negativeCycle,
    double timeMs)
{
    ofstream output(outputFile);

    if (!output.is_open())
    {
        throw runtime_error(
            "Cannot create output file: " + outputFile
        );
    }

    int V = static_cast<int>(dist.size());

    output << "========================================\n";
    output << "        FLOYD-WARSHALL RESULTS\n";
    output << "========================================\n\n";

    output << "Input File: " << inputFile << "\n";
    output << "Vertices: " << V << "\n\n";

    output << "Negative Cycle: "
           << (negativeCycle ? "Yes" : "No")
           << "\n\n";

    if (!negativeCycle)
    {
        output << "Distance Matrix:\n\n";

        for (int i = 0; i < V; ++i)
        {
            for (int j = 0; j < V; ++j)
            {
                if (dist[i][j] == INF)
                    output << "INF";
                else
                    output << dist[i][j];

                if (j + 1 < V)
                    output << "\t";
            }

            output << "\n";
        }
    }

    output << "\nExecution Time: "
           << fixed << setprecision(6)
           << timeMs << " ms\n";

    output.close();
}


// ============================================================
// Run Bellman-Ford
// ============================================================

void runBellmanFord(
    const fs::path& inputPath,
    const fs::path& outputPath)
{
    // Read graph
    Graph graph =
        readGraph(inputPath.string());

    // Convert to CSR BEFORE timing
    CSRGraph csr =
        CSR(graph);

    bool negativeCycle = false;

    // Start algorithm timing
    auto start =
        high_resolution_clock::now();

    vector<int> dist =
        bellmanFord(
            csr,
            graph.sourceVertex,
            negativeCycle
        );

    auto end =
        high_resolution_clock::now();

    double timeMs =
        duration<double, milli>(
            end - start
        ).count();

    // Save result
    writeBellmanOutput(
        outputPath.string(),
        inputPath.filename().string(),
        graph,
        dist,
        negativeCycle,
        timeMs
    );

    cout << "[BF] "
         << inputPath.filename().string()
         << "  ->  "
         << outputPath.filename().string()
         << "\n";
}


// ============================================================
// Run Floyd-Warshall
// ============================================================

void runFloydWarshall(
    const fs::path& inputPath,
    const fs::path& outputPath)
{
    // Read dense matrix directly
    vector<vector<int>> graph =
        readFloydInput(
            inputPath.string()
        );

    bool negativeCycle = false;

    // Start algorithm timing
    auto start =
        high_resolution_clock::now();

    vector<vector<int>> dist =
        Floyd_Warshall(
            graph,
            negativeCycle
        );

    auto end =
        high_resolution_clock::now();

    double timeMs =
        duration<double, milli>(
            end - start
        ).count();

    // Save result
    writeFloydOutput(
        outputPath.string(),
        inputPath.filename().string(),
        dist,
        negativeCycle,
        timeMs
    );

    cout << "[FW] "
         << inputPath.filename().string()
         << "  ->  "
         << outputPath.filename().string()
         << "\n";
}


// ============================================================
// MAIN
// ============================================================

int main()
{
    try
    {
        // Your exact folder structure
        fs::path inputDirectory =
            "testcase/input";

        fs::path outputDirectory =
            "testcase/output";


        // Create output folder automatically
        fs::create_directories(
            outputDirectory
        );


        if (!fs::exists(inputDirectory))
        {
            cerr << "Error: testcase/input folder not found.\n";
            return 1;
        }


        cout << "\n";
        cout << "========================================\n";
        cout << "             ASSIGNMENT 2\n";
        cout << "========================================\n\n";

        int bfCount = 0;
        int fwCount = 0;
        int failedCount = 0;

        for (const auto& entry :
             fs::directory_iterator(inputDirectory))
        {
            if (!entry.is_regular_file())
                continue;

            if (entry.path().extension() != ".txt")
                continue;


            string filename =
                entry.path().filename().string();

            string stem =
                entry.path().stem().string();


            fs::path outputPath =
                outputDirectory /
                (stem + "_output.txt");


            try
            {
                // -------------------------------
                // Bellman-Ford
                // -------------------------------

                if (stem.rfind("bf_", 0) == 0)
                {
                    runBellmanFord(
                        entry.path(),
                        outputPath
                    );

                    ++bfCount;
                }


                // -------------------------------
                // Floyd-Warshall
                // -------------------------------

                else if (stem.rfind("fw_", 0) == 0)
                {
                    runFloydWarshall(
                        entry.path(),
                        outputPath
                    );

                    ++fwCount;
                }


                // -------------------------------
                // Unknown file
                // -------------------------------

                else
                {
                    cout << "[SKIP] "
                         << filename
                         << " - unknown file prefix\n";
                }
            }
            catch (const exception& e)
            {
                cerr << "[ERROR] "
                     << filename
                     << " : "
                     << e.what()
                     << "\n";

                ++failedCount;
            }
        }


        // ====================================================
        // Summary
        // ====================================================

        cout << "Bellman-Ford tests  : "
             << bfCount << "\n";

        cout << "Floyd-Warshall tests: "
             << fwCount << "\n";

        cout << "Failed tests        : "
             << failedCount << "\n";

        cout << "\nOutput files saved in:\n";
        cout << "testcase/output/\n";

        cout << "\nProgram completed.\n";

        return failedCount == 0 ? 0 : 1;
    }
    catch (const exception& e)
    {
        cerr << "\nFatal Error: "
             << e.what()
             << "\n";

        return 1;
    }
}