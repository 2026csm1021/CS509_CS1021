#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <limits>
#include <string>

namespace fs = std::filesystem;

namespace {

int runInDirectory(const fs::path& directory, const std::string& command)
{
    if (!fs::exists(directory))
    {
        std::cerr << "Directory not found: " << directory << '\n';
        return 1;
    }

    return std::system(("cd /d \"" + directory.string() + "\" && " + command).c_str());
}

int runAssignment1(const fs::path& root)
{
    const fs::path temporaryExecutable = fs::temp_directory_path() / "cs509_assignment1.exe";
    const std::string buildAndRun =
        "g++ -std=c++17 -Iinclude src/wrapper.cpp src/gemm.cpp src/csr.cpp src/main.cpp "
        "-o \"" + temporaryExecutable.string() + "\" && \"" +
        temporaryExecutable.string() + "\"";

    return runInDirectory(root / "Assignment 1", buildAndRun);
}

int runAssignment2(const fs::path& root)
{
    const fs::path temporaryExecutable = fs::temp_directory_path() / "cs509_assignment2.exe";
    const std::string buildAndRun =
        "g++ -std=c++17 driver.cpp graph.cpp csr.cpp bellmanFord.cpp Floyd_Warshall.cpp "
        "-o \"" + temporaryExecutable.string() + "\" && \"" +
        temporaryExecutable.string() + "\"";

    return runInDirectory(root / "Assignment 2", buildAndRun);
}

int runAssignment3(const fs::path& root)
{
    const fs::path temporaryExecutable = fs::temp_directory_path() / "cs509_assignment3.exe";
    const std::string buildAndRun =
        "g++ -std=c++17 Driver.cpp CSR.cpp DSU.cpp graph.cpp kruskal.cpp prim.cpp "
        "-o \"" + temporaryExecutable.string() + "\" && \"" +
        temporaryExecutable.string() + "\"";

    return runInDirectory(root / "Assignment 3", buildAndRun);
}

bool isProjectRoot(const fs::path& directory)
{
    return fs::exists(directory / "Assignment 1") &&
           fs::exists(directory / "Assignment 2") &&
           fs::exists(directory / "Assignment 3");
}

} 

int main(int argc, char* argv[])
{
    fs::path root = fs::current_path();

    if (!isProjectRoot(root) && argc > 0)
    {
        root = fs::absolute(argv[0]).parent_path();
    }

    if (!isProjectRoot(root))
    {
        std::cerr << "Run this program from the CS509_CS1021 project directory.\n";
        return 1;
    }

    while (true)
    {
        std::cout << "\nCS509_CS1021 Assignment Wrapper\n"
                  << "1. Assignment 1 (GEMM / CSR)\n"
                  << "2. Assignment 2 (Bellman-Ford / Floyd-Warshall)\n"
                  << "3. Assignment 3 (Kruskal / Prim MST)\n"
                  << "0. Exit\n"
                  << "Enter choice: ";

        int choice;
        if (!(std::cin >> choice))
        {
            std::cerr << "Please enter a number.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }

        int result = 0;
        switch (choice)
        {
        case 1:
            result = runAssignment1(root);
            break;
        case 2:
            result = runAssignment2(root);
            break;
        case 3:
            result = runAssignment3(root);
            break;
        case 0:
            return 0;
        default:
            std::cerr << "Invalid choice.\n";
            continue;
        }

        if (result != 0)
        {
            std::cerr << "The selected assignment exited with code " << result << ".\n";
        }
    }
}
