#include <iostream>
#include <string>
#include <memory>

#include "parser.h"


int main(int argc, char *argv[])
{
    GraphParser p;
    Problem_t problem;

    p.parse("test.map", problem);
    //p.parse("test10k-dir.map", problem);

    std::cout << "Name: " << problem.name << "\n";

    std::cout << "Commentary:" << "\n";
    for (auto i : problem.comment)
    {
        std::cout << "\t    " << i << "\n";
    }

    std::cout << "\n";
    std::cout << "Map dimension: " << problem.dimension << "\n";
    std::cout << "Directed: " << (problem.directed ? "True" : "False") << "\n";

    std::cout << "\n";
    std::cout << "Edge list: " << "\n";
    for (auto i : problem.edgeList)
    {
        for (auto j : i)
            std::cout << j << " ";

        std::cout << "\n";
    }

    std::cout << "\n";
    std::cout << "Weight list: " << "\n";
    for (auto i : problem.weightList)
    {
        for (auto j : i)
            std::cout << j << " ";

        std::cout << "\n";
    }

    return 0;
}
