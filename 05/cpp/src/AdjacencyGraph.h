/**
*   Implementace grafu pomoci matice sousednosti
*   viz. https://cs.wikipedia.org/wiki/Matice_sousednosti
*   
*   https://www.youtube.com/watch?v=6EzMdAskU9M
*   
*	New BSD License
*	https://www.vutbr.cz/studis/student.phtml?gm=gm_detail_predmetu&apid=158780
*
*	C language is all about speed. Hot, nasty, bad-ass speed. - Eleanor Roosevelt, 1936.
*/

#pragma once
//#include <iostream>
//#include <iomanip>
#include <algorithm>
#include <vector>
#include <string>

#include "IGraph.h"
#include "GraphDef.h"

class AdjecencyGraph : public IGraph
{
  public:
    AdjecencyGraph() = delete;
    AdjecencyGraph(const size_t size, const bool directed = false);
    virtual ~AdjecencyGraph();

    virtual void addVertex(const Vertex& v) override;

    virtual void
        addEdge(const size_t from, const size_t to, size_t dist) override;

    virtual Vertex* getVertex(const size_t idx) override;
    virtual Edge* getEdge(const size_t idx) override;
    virtual Edge* getEdge(const size_t from, const size_t to) override;
    virtual size_t getEdgesCount() override;
    virtual size_t getVertexCount() override;

    virtual std::vector<std::pair<size_t, size_t>>
        getAdjecent(const size_t from) override;

    virtual bool isConnected(const size_t from, const size_t to) override;

    // DEBUG funkce pro tisknuti vlastnosti u malych grafu
    void printMatrix();
    void printEdgeMatrix();
    void printDistMatrix();
    void printVertices();

  protected:
    void makeEmpty();
    bool vertexExists(const Vertex& v);

  private:
    std::vector<std::vector<bool>> m_matrix;
    std::vector<std::vector<size_t>> m_edgeMatrix;

    std::vector<Edge*> m_edges;
    std::vector<Vertex> m_vertices;
};
