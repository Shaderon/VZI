#include <iostream>
#include <string>
#include <memory>

//#include "ListGraph.h"
#include "AdjacencyGraph.h"


int main(int argc, char *argv[])
{

    Graph<Vertex, Edge> g(5, true);
    
    for (auto i = 0; i < 5; ++i)
    {
        Vertex v;
        v.idx = i;
        
        g.addVertex(v);
    }    
    
    auto *e1 = new Edge();
    e1->idx = 0;
    e1->distance = 1;
    g.addEdge(0, 1, e1);

    auto *e2 = new Edge();
    e2->idx = 1;
    e2->distance = 1;
    g.addEdge(0, 2, e2);

    auto *e3 = new Edge();
    e3->idx = 2;
    e3->distance = 1;
    g.addEdge(0, 1, e3);

    auto *e4 = new Edge();
    e4->idx = 3;
    e4->distance = 1;
    g.addEdge(0, 2, e4);

    auto *e5 = new Edge();
    e5->idx = 4;
    e5->distance = 1;
    g.addEdge(0, 1, e5);

    auto *e6 = new Edge();
    e6->idx = 5;
    e6->distance = 1;
    g.addEdge(0, 2, e6);


    g.printMatrix();
    printf("-------------\n");

    g.printDistMatrix();
    printf("-------------\n");

    g.printEdgeMatrix();
    printf("-------------\n");

    g.printVertices();
    printf("-------------\n");


    printf("\n\n");
    return 0;
}