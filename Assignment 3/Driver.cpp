#include <iostream>
#include <chrono>
#include <fstream>
#include <string>

#include "Graph.h"
#include "CSR.h"
#include "Kruskal.h"
#include "Prim.h"

using namespace std;
using namespace chrono;


void printResult(const string& algorithmName, const MSTResult& result, double timeMs)
{
    cout << "Algorithm: " << algorithmName <<endl;

    if (!result.connected)
    {
        cout << "Error: input graph is disconnected. No valid MST exists.\n";
        cout << "Execution time: " << timeMs << " ms"<<endl;
        return;
    }

    cout << "MST edges: "<<endl;

    for (const auto& edge : result.edges)
    {
        cout << edge.u << " " << edge.v << " " << edge.weight << endl;
    }

    cout << "Total MST weight: " << result.totalWeight << endl;
    cout << "Execution time: " << timeMs << " ms" << endl;
}


bool fileExists(const string& path)
{
    ifstream f(path);
    return f.good();
}


void runChoice(int choice, const string& filename)
{
    if (!fileExists(filename))
    {
        cout << "Error: input file does not exist or cannot be opened: " << filename <<endl;
        return;
    }

    try
    {
        Graph graph = readGraph(filename);

        validateGraph(graph);

        cout << "Vertices: " << graph.V << endl;
        cout << "Edges: " << graph.E << endl;

        CSR csr = convertToCSR(graph);

        // Output file
        string outputFilename =
            "testcases/output/mst_" +
            to_string(graph.V) +
            "_output.txt";

        ofstream outputFile(outputFilename);

        if (!outputFile)
        {
            cout << "Error: cannot create output file: "
                 << outputFilename << endl;
            return;
        }

        outputFile << "CS509 Assignment 3 - MST" << endl;
        outputFile << "Input File: " << filename << endl;
        outputFile << "Vertices: " << graph.V << endl;
        outputFile << "Edges: " << graph.E << endl;


        if (choice == 1 || choice == 3)
        {
            auto start = high_resolution_clock::now();
            MSTResult kruskalResult = kruskalMST(csr);
            auto stop = high_resolution_clock::now();

            double kruskalTime =
                duration<double, milli>(stop - start).count();

            printResult("Kruskal's MST", kruskalResult, kruskalTime);

            outputFile << "\nAlgorithm: Kruskal's MST" << endl;

            if (!kruskalResult.connected)
            {
                outputFile << "Error: input graph is disconnected. No valid MST exists."
                           << endl;
                outputFile << "Execution time: "
                           << kruskalTime << " ms" << endl;
            }
            else
            {
                outputFile << "MST edges:" << endl;

                for (const auto& edge : kruskalResult.edges)
                {
                    outputFile << edge.u << " "
                               << edge.v << " "
                               << edge.weight << endl;
                }

                outputFile << "Total MST weight: "
                           << kruskalResult.totalWeight << endl;

                outputFile << "Execution time: "
                           << kruskalTime << " ms" << endl;
            }


            if (choice == 3)
            {
                auto start2 = high_resolution_clock::now();
                MSTResult primResult = primMST(csr);
                auto stop2 = high_resolution_clock::now();

                double primTime =
                    duration<double, milli>(stop2 - start2).count();

                printResult("Prim's MST", primResult, primTime);

                outputFile << "\nAlgorithm: Prim's MST" << endl;

                if (!primResult.connected)
                {
                    outputFile << "Error: input graph is disconnected. No valid MST exists."
                               << endl;
                    outputFile << "Execution time: "
                               << primTime << " ms" << endl;
                }
                else
                {
                    outputFile << "MST edges:" << endl;

                    for (const auto& edge : primResult.edges)
                    {
                        outputFile << edge.u << " "
                                   << edge.v << " "
                                   << edge.weight << endl;
                    }

                    outputFile << "Total MST weight: "
                               << primResult.totalWeight << endl;

                    outputFile << "Execution time: "
                               << primTime << " ms" << endl;
                }


                cout << "\nComparison:\n";
                cout << "Kruskal MST weight: "
                     << kruskalResult.totalWeight << endl;

                cout << "Prim MST weight: "
                     << primResult.totalWeight << endl;

                outputFile << "\nComparison:" << endl;

                outputFile << "Kruskal MST weight: "
                           << kruskalResult.totalWeight << endl;

                outputFile << "Prim MST weight: "
                           << primResult.totalWeight << endl;


                if (kruskalResult.connected && primResult.connected &&
                    kruskalResult.totalWeight == primResult.totalWeight)
                {
                    cout << "MST weights are equal: YES\n";
                    outputFile << "MST weights are equal: YES" << endl;
                }
                else
                {
                    cout << "MST weights are equal: NO\n";
                    outputFile << "MST weights are equal: NO" << endl;
                }
            }
        }
        else if (choice == 2)
        {
            auto start = high_resolution_clock::now();
            MSTResult primResult = primMST(csr);
            auto stop = high_resolution_clock::now();

            double primTime =
                duration<double, milli>(stop - start).count();

            printResult("Prim's MST", primResult, primTime);

            outputFile << "\nAlgorithm: Prim's MST" << endl;

            if (!primResult.connected)
            {
                outputFile << "Error: input graph is disconnected. No valid MST exists."
                           << endl;
                outputFile << "Execution time: "
                           << primTime << " ms" << endl;
            }
            else
            {
                outputFile << "MST edges:" << endl;

                for (const auto& edge : primResult.edges)
                {
                    outputFile << edge.u << " "
                               << edge.v << " "
                               << edge.weight << endl;
                }

                outputFile << "Total MST weight: "
                           << primResult.totalWeight << endl;

                outputFile << "Execution time: "
                           << primTime << " ms" << endl;
            }
        }
        else
        {
            cout << "Error: invalid algorithm choice." << endl;
            outputFile << "Error: invalid algorithm choice." << endl;
        }

        outputFile.close();

        cout << "\nOutput saved to: "
             << outputFilename << endl;
    }
    catch (const exception& e)
    {
        cout << "Error: " << e.what() << endl;
    }
}


void runMenu()
{
    while (true)
    {
        cout << "CS509 Assignment 3 - MST " << endl;
        cout << "1. Run Kruskal" << endl;
        cout << "2. Run Prim" << endl;
        cout << "3. Run Both MST Algorithms" << endl;
        cout << "4. Exit" << endl;

        cout << "Enter choice: " << endl;

        int choice;
        cin >> choice;

        if (choice == 4)
        {
            cout << "Exiting." << endl;
            return;
        }

        if (choice < 1 || choice > 4)
        {
            cout << "Error: invalid choice." << endl;
            continue;
        }

        cout << endl;

        // Select graph size
        cout << "Select graph size:" << endl;
        cout << "1. 10 vertices" << endl;
        cout << "2. 100 vertices" << endl;

        cout << "Enter graph size choice: ";

        int sizeChoice;
        cin >> sizeChoice;

        int vertices;

        switch (sizeChoice)
        {
            case 1:
                vertices = 10;
                break;

            case 2:
                vertices = 100;
                break;

            default:
                cout << "Error: invalid graph size." << endl;
                continue;
        }

        string filename =
            "testcases/input/mst_" +
            to_string(vertices) +
            ".txt";

        cout << "Using input file: "
             << filename << endl;

        runChoice(choice, filename);
    }
}


int main(int argc, char* argv[])
{
    if (argc == 3)
    {
        int choice = stoi(argv[1]);
        string filename = argv[2];

        runChoice(choice, filename);

        return 0;
    }

    runMenu();

    return 0;
}