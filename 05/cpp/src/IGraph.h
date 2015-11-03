/**
*   Implementace base tridy grafu, 
*   z teto tridy budou naslednici dedit zakladni rozhrani
*
*	New BSD License
*	https://www.vutbr.cz/studis/student.phtml?gm=gm_detail_predmetu&apid=158780
*
*	C language is all about speed. Hot, nasty, bad-ass speed. - Eleanor Roosevelt, 1936.
*/

#pragma once
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

#include "GraphDef.h"


class IGraph
{
public:

    IGraph() = delete;

    IGraph(const size_t size, const bool directed = false)
    {
        m_size = size;
        m_directed = directed;
    };
    
    ~IGraph(){};

    virtual void    addVertex(const Vertex& v) = 0;
    virtual void    addEdge(const size_t from, const size_t to, size_t dist) = 0;
    virtual Vertex* getVertex(const size_t idx) = 0;
    virtual Edge*   getEdge(const size_t idx)= 0;
    virtual Edge*   getEdge(const size_t from, const size_t to) = 0;
    virtual size_t  getEdgesCount() = 0;
    virtual size_t  getVertexCount() = 0;

    virtual std::vector<std::pair<size_t, size_t>> getAdjecent(const size_t from) = 0;
    virtual bool isConnected(const size_t from, const size_t to) = 0;
protected:

    size_t m_size;
    bool   m_directed;
};

