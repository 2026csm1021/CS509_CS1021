#include <iostream>
#include <string>
#include <chrono>
#include <vector>

#include "Graph.h"
#include "CSR.h"
#include "VertexColoring.h"

using namespace std;
using namespace chrono;

int main()
{
    string filename;

    cout << "Enter input file name: ";
    cin >> filename;

    try
    {
        Graph graph = readGraph(filename);

        validateGraph(graph);

        CSR csr = convertToCSR(graph);

        auto startTime = high_resolution_clock::now();

        vector<int> colors = vertexColoring(csr);

        auto endTime = high_resolution_clock::now();

        double timeTaken =
            duration<double, milli>(
                endTime - startTime
            ).count();

        int numberOfColors = 0;

        for (int i = 0; i < csr.V; i++)
        {
            if (colors[i] > numberOfColors)
            {
                numberOfColors = colors[i];
            }
        }

        cout << "\nVertex Coloring:\n";

        for (int i = 0; i < csr.V; i++)
        {
            cout << "Vertex "
                 << i
                 << " : Color "
                 << colors[i]
                 << endl;
        }

        cout << "\nNumber of Colors: "
             << numberOfColors
             << endl;

        cout << "Coloring Time: "
             << timeTaken
             << " ms"
             << endl;
    }
    catch (const exception& e)
    {
        cout << "Error: "
             << e.what()
             << endl;
    }

    return 0;
}