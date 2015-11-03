#include <iostream>
#include <string>
#include <vector>

#include "parser.h"
#include "GraphDef.h"
#include "IGraph.h"
#include "AdjacencyGraph.h"
#include "Dijkstra.h"

void test1()
{
    // nas ukazkovy graf
    // Graph
    //
    //      1 * --- *3
    //     * *       * \
    //    /  |       |  *
    //   0   |       |   5
    //    \  |       |  *
    //     * *       * /
    //      2 * --- *4
    //

    AdjecencyGraph g(6, true); // vytvorime nas graf

    for (auto i = 0; i < 6; ++i)
    {
        Vertex v;
        v.idx = i;
        g.addVertex(v);
    }

    // pridame hrany 
    g.addEdge(0, 1, 1);
    g.addEdge(0, 2, 5);
    g.addEdge(1, 2, 2);
    g.addEdge(1, 3, 4);
    g.addEdge(2, 1, 1);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 9);
    g.addEdge(3, 5, 2);
    g.addEdge(4, 3, 4);
    g.addEdge(4, 5, 5);

    g.printMatrix();
    printf("-------------\n");

    g.printDistMatrix();
    printf("-------------\n");

    g.printEdgeMatrix();
    printf("-------------\n");

    auto start = g.getVertex(0);
    auto finish = g.getVertex(g.getVertexCount() - 1);

    Dijkstra djk(&g); // budeme hledat cestu pomoci dijkstrova algoritmu

    std::cout << "Start node: " << start->idx << "\n";
    std::cout << "End node  : " << finish->idx << "\n";

    auto ret = djk.search(start, finish);

    std::cout << "Route     : ";
    for (uint32_t i = 0; i < ret.size() - 1; ++i)
    {
        std::cout << ret[i]->idx << "->";
    }
    std::cout << ret[ret.size() - 1]->idx << "\n\n";

}

void test2()
{
    GraphParser p;
    Problem_t problem;

    p.parse("test.map", problem);
    //p.parse("test100-dir.map", problem);
    
    auto sz = problem.dimension;
    auto directed = problem.directed;

    // vytvorime nas graf
    AdjecencyGraph g(sz, directed);

    // prvne pridame uzly
    for (auto i = 0; i < sz; ++i)
    {
        Vertex v;
        v.idx = i;
        g.addVertex(v);
    }
        
    // pridame hrany
    // problem.edgesList a .weightList jsou matice, kde index radku je index uzlu
    // (obe matice maji stejnou velikost) a kazdy radek obsahuje info o hranach
    // pr: edgeList[0] jsou ulozeny idx uzlu kam smeruji hrany z uzlu 0
    // pr: weightList[0] jsou ulozeny ohodnoceni hran 
    // 
    for (auto i = 0; i < sz; ++i) 
    {
        auto startNode = i;
        auto edgesCount = problem.edgeList[i].size(); 

        for (auto j = 0; j < edgesCount; ++j)
        {
            auto endNode = problem.edgeList[i][j];
            auto weight  = problem.weightList[i][j];

            g.addEdge(startNode, endNode, weight);
        }
    }

    // a ted uz zbyva jen hledani SP
    Dijkstra djk(&g); // budeme hledat cestu pomoci dijkstrova algoritmu
    
    auto start = g.getVertex(0);
    auto finish = g.getVertex(g.getVertexCount() - 1);

    std::cout << "Start node: " << start->idx << "\n";
    std::cout << "End node  : " << finish->idx << "\n";

    auto ret = djk.search(start, finish);

    std::cout << "Route     : ";
    for (uint32_t i = 0; i < ret.size() - 1; ++i)
    {
        std::cout << ret[i]->idx << "->";
    }
    std::cout << ret[ret.size() - 1]->idx << "\n\n";

}


int main(int argc, char *argv[])
{
    test1();

    std::cout << "---------------------------\n";

    test2();

    return 0;
}