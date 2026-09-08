#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
#include <utility>
#include <vector>

#include "Graph.h"
#include "CSR.h"
#include "PageRank.h"
#include "VertexColoring.h"

using namespace std;
using namespace chrono;

bool fileExists(const string& filename)
{
    ifstream file(filename);
    return file.good();
}

void runVertexColoring(const string& filename)
{
    if (!fileExists(filename))
    {
        cout << "Error: input file does not exist or cannot be opened.\n";
        return;
    }

    try
    {
        Graph graph = readGraph(filename);
        validateVertexColoringGraph(graph);

        CSR csr = convertToCSR(graph);

        auto start = high_resolution_clock::now();
        vector<int> colors = vertexColoring(csr);
        auto stop = high_resolution_clock::now();

        double timeTaken =
            duration<double, milli>(stop - start).count();

        int numberOfColors = 0;
        for (int color : colors)
        {
            if (color > numberOfColors)
                numberOfColors = color;
        }

        cout << "\nAlgorithm: Greedy Vertex Coloring\n";
        cout << "Input file: " << filename << "\n";
        cout << "Vertex colors:\n";

        for (int i = 0; i < csr.V; i++)
        {
            cout << i << " " << colors[i] << "\n";
        }

        cout << "Colors used: " << numberOfColors << "\n";
        cout << "Execution time: " << timeTaken << " ms\n";
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

void runPageRank(const string& filename)
{
    if (!fileExists(filename))
    {
        cout << "Error: input file does not exist or cannot be opened.\n";
        return;
    }

    try
    {
        Graph graph = readGraph(filename);
        validatePageRankGraph(graph);

        CSR csr = convertToCSR(graph);

        auto start = high_resolution_clock::now();

        PageRankResult result = pageRank(
            csr,
            graph.damping,
            graph.tolerance,
            graph.maxIterations
        );

        auto stop = high_resolution_clock::now();

        double timeTaken =
            duration<double, milli>(stop - start).count();

        cout << "\nAlgorithm: PageRank\n";
        cout << "Input file: " << filename << "\n";
        cout << "Vertex ranks:\n";

        for (int i = 0; i < csr.V; i++)
        {
            cout << i << " " << result.rank[i] << "\n";
        }

        cout << "Iterations: " << result.iterations << "\n";
        cout << "Converged: "
             << (result.converged ? "true" : "false")
             << "\n";
        cout << "Execution time: " << timeTaken << " ms\n";
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << "\n";
    }
}

int chooseInputFile(
    const string& title,
    const vector<pair<string, string>>& files)
{
    while (true)
    {
        cout << "\n" << title << "\n";

        for (int i = 0; i < (int)files.size(); i++)
        {
            cout << i + 1 << ". " << files[i].first << "\n";
        }

        cout << "0. Back\n";
        cout << "Enter choice: ";

        int choice;

        if (!(cin >> choice))
        {
            cout << "Error: invalid choice.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0)
            return -1;

        if (choice >= 1 && choice <= (int)files.size())
        {
            return choice - 1;
        }

        cout << "Error: invalid choice.\n";
    }
}

void vertexColoringMenu()
{
    const vector<pair<string, string>> inputFiles =
    {
        {"coloring.txt", "input/coloring.txt"},
        {"coloring_10.txt", "input/coloring_10.txt"},
        {"coloring_100.txt", "input/coloring_100.txt"},
        {"coloring_1000.txt", "input/coloring_1000.txt"},
        {"coloring_10000.txt", "input/coloring_10000.txt"},
        {"coloring_50000.txt", "input/coloring_50000.txt"},
        {"coloring_100000.txt", "input/coloring_100000.txt"}
    };

    int choice = chooseInputFile("Vertex Coloring Input Files", inputFiles);

    if (choice != -1)
        runVertexColoring(inputFiles[choice].second);
}

void pageRankMenu()
{
    const vector<pair<string, string>> inputFiles =
    {
        {"pagerank.txt", "input/pagerank.txt"},
        {"pagerank_dangling.txt", "input/pagerank_dangling.txt"},
        {"pagerank_10.txt", "input/pagerank_10.txt"},
        {"pagerank_100.txt", "input/pagerank_100.txt"},
        {"pagerank_1000.txt", "input/pagerank_1000.txt"},
        {"pagerank_10000.txt", "input/pagerank_10000.txt"},
        {"pagerank_50000.txt", "input/pagerank_50000.txt"}
    };

    int choice = chooseInputFile("PageRank Input Files", inputFiles);

    if (choice != -1)
        runPageRank(inputFiles[choice].second);
}

int main()
{
    while (true)
    {
        cout << "\nCS509 Assignment 4\n";
        cout << "1. Vertex Coloring\n";
        cout << "2. PageRank\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";

        int choice;

        if (!(cin >> choice))
        {
            cout << "Error: invalid choice.\n";
            cin.clear();
            cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 0)
            return 0;

        if (choice == 1)
            vertexColoringMenu();
        else if (choice == 2)
            pageRankMenu();
        else
            cout << "Error: invalid choice.\n";
    }
}
