#include "Dijkstra.h"

std::vector<Vertex*> Dijkstra::search(Vertex *start, Vertex *finish)
{
    std::vector<Vertex*> notVisited;

    // prvne provedeme inicializaci, kde nastavime pro kazdy uzel v grafu
    // polozku value na nekonecno (v nasem pripade je to max. hodnota typu)
    // polozku visited na false, tj. vsechny uzly jsou nenavstiveny
    // polozku pred, tj. predchozi uzel na nullptr (tj. NULL)
    for (auto i = 0; i < g->getVertexCount(); ++i)
    {
        auto v = g->getVertex(i);
        v->value = DJK_INFINITY;
        v->visited = false;
        v->pred = nullptr;

        notVisited.push_back(v);
    }

    // u startovniho uzlu nastavime ohodnoceni na 0
    start->value = 0;

    while (!notVisited.empty())
    {
        // ze vsech uzlu vybereme ten s nejmensim ohodnocenim
        // takze prvne to bude nas start uzel (ma ohodnoceni 0)
        Vertex *actual = getNodeWithMinValue(notVisited);

        // zjistime vsechny uzly do kterych smeruji hrany z daneho uzlu
        // v tomto pripade getAdjecent vraci pole paru (std::vector<std::pair>)
        // takze polozka .first je index uzlu do ktereho smeruje hrana
        // polozka .second je index hrany, ktera vede do .first uzlu
        auto vec = g->getAdjecent(actual->idx);

        for (size_t i = 0; i < vec.size(); ++i)
        {
            auto v = g->getVertex(vec[i].first); // vezmeme si uzel
            auto e = g->getEdge(vec[i].second);  // a hranu

            auto weight = actual->value + e->distance; // vypocteme ohodnoceni

            if (weight < v->value) // a porovname
            {
                v->value = weight;
                v->pred = actual;
            }
        }
    }

    // najdeme cestu zpatky z cile na start
    std::vector<Vertex*> route;
    backtrackGraph(route, finish);

    return route;
}

Vertex* Dijkstra::getNodeWithMinValue(std::vector<Vertex*>& notVisited)
{
    std::sort(notVisited.begin(), notVisited.end(), [&notVisited]
        (Vertex *a, Vertex *b)
    {
        return (a->value > b->value);
    });

    auto *result = notVisited[notVisited.size() - 1];
    notVisited.pop_back();

    return result;
}

void Dijkstra::backtrackGraph(std::vector<Vertex *>& route, Vertex *target)
{
    while (target->pred)
    {
        route.push_back(target);
        target = target->pred;
    }
    // pridame posledni uzel
    route.push_back(target);

    // otocime, taky aby cesta vedla ze startu do cile
    std::reverse(route.begin(), route.end());
}
