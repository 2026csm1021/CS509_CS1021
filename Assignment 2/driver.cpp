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

vector<vector<int>> readFloydInput(const string& filename)
{
    ifstream input(filename);

    if (!input)
        throw runtime_error("Cannot open file: " + filename);

    int V;
    input >> V;

    vector<vector<int>> graph(V, vector<int>(V, INF));

    for (int i = 0; i < V; ++i)
    {
        for (int j = 0; j < V; ++j)
        {
            string value;
            input >> value;

            if (value == "INF" || value == "inf")
                graph[i][j] = INF;
            else
                graph[i][j] = stoi(value);
        }
    }

    return graph;
}

void writeBellmanOutput(
    const string& file,
    const Graph& graph,
    const vector<int>& dist,
    bool negativeCycle,
    double timeMs)
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

        for (int v = 0; v < graph.totalVertices; ++v)
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
}

void writeFloydOutput(
    const string& file,
    const vector<vector<int>>& dist,
    bool negativeCycle,
    double timeMs)
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
}

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

    double timeMs =
        duration<double, milli>(end - start).count();

    writeBellmanOutput(
        outputFile.string(),
        graph,
        dist,
        negativeCycle,
        timeMs
    );

    cout << "[BF] "
         << inputFile.filename().string()
         << " -> "
         << outputFile.filename().string()
         << "\n";
}

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

    double timeMs =
        duration<double, milli>(end - start).count();

    writeFloydOutput(
        outputFile.string(),
        dist,
        negativeCycle,
        timeMs
    );

    cout << "[FW] "
         << inputFile.filename().string()
         << " -> "
         << outputFile.filename().string()
         << "\n";
}

int main()
{
    try
    {
        fs::path inputDir = "testcase/input";
        fs::path outputDir = "testcase/output";

        fs::create_directories(outputDir);

        if (!fs::exists(inputDir))
        {
            cerr << "Error: testcase/input not found.\n";
            return 1;
        }

        vector<fs::path> files;

        for (const auto& entry : fs::directory_iterator(inputDir))
        {
            if (entry.is_regular_file() &&
                entry.path().extension() == ".txt")
            {
                files.push_back(entry.path());
            }
        }

        sort(files.begin(), files.end());

        int outputNumber = 1;
        int bfCount = 0;
        int fwCount = 0;
        int failedCount = 0;

        cout << "\nAssignment 2\n";
        cout << "-------------\n";

        for (const auto& inputFile : files)
        {
            string name = inputFile.stem().string();

            bool isBF = name.rfind("bf_input_", 0) == 0;
            bool isFW = name.rfind("fw_input_", 0) == 0;

            if (!isBF && !isFW)
                continue;

            fs::path outputFile =
                outputDir /
                ("output_" +
                 to_string(outputNumber) +
                 ".txt");

            try
            {
                if (isBF)
                {
                    runBellmanFord(inputFile, outputFile);
                    ++bfCount;
                }
                else
                {
                    runFloydWarshall(inputFile, outputFile);
                    ++fwCount;
                }

                ++outputNumber;
            }
            catch (const exception& e)
            {
                cerr << "[ERROR] "
                     << inputFile.filename().string()
                     << ": "
                     << e.what() << "\n";

                ++failedCount;
            }
        }

        cout << "\nSummary\n";
        cout << "-------\n";
        cout << "Bellman-Ford   : " << bfCount << "\n";
        cout << "Floyd-Warshall : " << fwCount << "\n";
        cout << "Failed         : " << failedCount << "\n";
        cout << "Output folder  : testcase/output\n";

        return failedCount == 0 ? 0 : 1;
    }
    catch (const exception& e)
    {
        cerr << "Fatal Error: " << e.what() << "\n";
        return 1;
    }
}