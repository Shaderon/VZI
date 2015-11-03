#pragma once

#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

const size_t NON_EDGE = std::numeric_limits<size_t>::max();

typedef struct Vertex
{
    size_t  idx;    // 0-X
    size_t  value;  // pro dijkstruv algoritmus
    Vertex *pred;
    bool    visited;

    Vertex()
    {
        idx = 0;
        value = 0;
        pred = nullptr;
        visited = false;
    }

    bool operator == (const Vertex &a) const
    {
        if (idx == a.idx) return true;
        else
            return false;
    };

    friend std::ostream& operator << (std::ostream& os, const Vertex& v);

} vertex_t;

// DEBUG, pro vypsani hodnot uzlu 
static std::ostream& operator << (std::ostream& os, const Vertex& v)
{
    os << v.idx;
    return os;
}


typedef struct Edge
{
    size_t idx;
    size_t distance;

    Edge()
    {
        idx = distance = 0;
    };

    friend std::ostream& operator << (std::ostream& os, const Edge& e);

} edge_t;


//DEBUG, pro vypsani hodnot o hrane
static std::ostream& operator << (std::ostream& os, const Edge& e)
{
    os << e.distance;
    return os;
}
