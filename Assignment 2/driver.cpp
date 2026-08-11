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


// Read Floyd-Warshall input
vector<vector<int>> readFloydInput(const string& file)
{
    ifstream input(file);

    if (!input)
        throw runtime_error("Cannot open file: " + file);

    int V;
    input >> V;

    vector<vector<int>> graph(V, vector<int>(V, INF));

    for (int i = 0; i < V; i++)
    {
        for (int j = 0; j < V; j++)
        {
            string x;
            input >> x;

            graph[i][j] =
                (x == "INF" || x == "inf") ? INF : stoi(x);
        }
    }

    return graph;
}


// Write Bellman-Ford output
void writeBellmanOutput(
    const string& file,
    const Graph& graph,
    const vector<int>& dist,
    bool negativeCycle,
    double time)
{
    ofstream output(file);

    output << "Algorithm: Bellman-Ford\n";
    output << "Vertices: " << graph.totalVertices << "\n";
    output << "Edges: " << graph.totalEdges << "\n";
    output << "Source: " << graph.sourceVertex << "\n";
    output << "Negative Cycle: "
           << (negativeCycle ? "Yes" : "No") << "\n\n";

    if (!negativeCycle)
    {
        output << "Vertex\tDistance\n";

        for (int v = 0; v < graph.totalVertices; v++)
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
           << time << " ms\n";
}


// Write Floyd-Warshall output
void writeFloydOutput(
    const string& file,
    const vector<vector<int>>& dist,
    bool negativeCycle,
    double time)
{
    ofstream output(file);

    int V = dist.size();

    output << "Algorithm: Floyd-Warshall\n";
    output << "Vertices: " << V << "\n";
    output << "Negative Cycle: "
           << (negativeCycle ? "Yes" : "No") << "\n\n";

    if (!negativeCycle)
    {
        output << "Distance Matrix:\n";

        for (int i = 0; i < V; i++)
        {
            for (int j = 0; j < V; j++)
            {
                if (dist[i][j] == INF)
                    output << "INF";
                else
                    output << dist[i][j];

                if (j < V - 1)
                    output << "\t";
            }

            output << "\n";
        }
    }

    output << "\nExecution Time: "
           << fixed << setprecision(6)
           << time << " ms\n";
}


// Run Bellman-Ford
void runBellmanFord(
    const fs::path& inputFile,
    const fs::path& outputFile)
{
    Graph graph = readGraph(inputFile.string());
    CSRGraph csr = CSR(graph);

    bool negativeCycle = false;

    auto start = high_resolution_clock::now();

    vector<int> dist =
        bellmanFord(csr, graph.sourceVertex, negativeCycle);

    auto end = high_resolution_clock::now();

    double time =
        duration<double, milli>(end - start).count();

    writeBellmanOutput(
        outputFile.string(),
        graph,
        dist,
        negativeCycle,
        time
    );

}


// Run Floyd-Warshall
void runFloydWarshall(
    const fs::path& inputFile,
    const fs::path& outputFile)
{
    vector<vector<int>> graph =
        readFloydInput(inputFile.string());

    bool negativeCycle = false;

    auto start = high_resolution_clock::now();

    vector<vector<int>> dist =
        Floyd_Warshall(graph, negativeCycle);

    auto end = high_resolution_clock::now();

    double time =
        duration<double, milli>(end - start).count();

    writeFloydOutput(
        outputFile.string(),
        dist,
        negativeCycle,
        time
    );

}


// Main
int main()
{
    try
    {
        fs::path inputDir = "testcase/input";
        fs::path outputDir = "testcase/output";

        if (!fs::exists(inputDir))
        {
            cerr << "Error: testcase/input not found.\n";
            return 1;
        }

        fs::create_directories(outputDir);

        vector<fs::path> bfFiles;
        vector<fs::path> fwFiles;

        // Find input files
        for (const auto& entry : fs::directory_iterator(inputDir))
        {
            if (!entry.is_regular_file() ||
                entry.path().extension() != ".txt")
                continue;

            string name = entry.path().stem().string();

            if (name.rfind("bf_input_", 0) == 0)
                bfFiles.push_back(entry.path());

            else if (name.rfind("fw_input_", 0) == 0)
                fwFiles.push_back(entry.path());
        }

        // Sort input files
        sort(bfFiles.begin(), bfFiles.end());
        sort(fwFiles.begin(), fwFiles.end());

        int outputNumber = 1;
        int bfCount = 0;
        int fwCount = 0;
        int failedCount = 0;

        // Bellman-Ford
        for (const auto& inputFile : bfFiles)
        {
            try
            {
                fs::path outputFile =
                    outputDir /
                    ("output_" + to_string(outputNumber) + ".txt");

                runBellmanFord(inputFile, outputFile);

                outputNumber++;
                bfCount++;
            }
            catch (const exception& e)
            {
                cerr << "[ERROR] "
                     << inputFile.filename()
                     << ": "
                     << e.what()
                     << "\n";

                failedCount++;
            }
        }

        // Floyd-Warshall
        for (const auto& inputFile : fwFiles)
        {
            try
            {
                fs::path outputFile =
                    outputDir /
                    ("output_" + to_string(outputNumber) + ".txt");

                runFloydWarshall(inputFile, outputFile);

                outputNumber++;
                fwCount++;
            }
            catch (const exception& e)
            {
                cerr << "[ERROR] "
                     << inputFile.filename()
                     << ": "
                     << e.what()
                     << "\n";

                failedCount++;
            }
        }

        // Summary
        cout << "\n-------------------------\n";
        cout << "Bellman-Ford   : " << bfCount << "\n";
        cout << "Floyd-Warshall : " << fwCount << "\n";
        cout << "Failed         : " << failedCount << "\n";
        cout << "Output folder  : testcase/output\n";
        cout << "-------------------------\n";

        return failedCount == 0 ? 0 : 1;
    }
    catch (const exception& e)
    {
        cerr << "Fatal Error: " << e.what() << "\n";
        return 1;
    }
}