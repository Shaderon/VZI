// Implementace Dijkstrova hledani nejkratsi cesty v grafu
// viz. https://en.wikipedia.org/wiki/Dijkstra's_algorithm

#pragma once
#include <vector>
#include <limits>
#include "GraphDef.h"
#include "IGraph.h"

const size_t DJK_INFINITY = std::numeric_limits<size_t>::max();

class Dijkstra
{
public:

    Dijkstra(IGraph *graph)
    {
        g = graph;
    };

    ~Dijkstra()
    { };

    std::vector<Vertex*> search(Vertex *start, Vertex *finish);

private:
    Vertex* getNodeWithMinValue(std::vector<Vertex*>& notVisited);
    void backtrackGraph(std::vector<Vertex *>& route, Vertex *target);

private:
    IGraph *g;
};