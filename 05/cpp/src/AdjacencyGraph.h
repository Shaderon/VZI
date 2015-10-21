/**
*
*   https://www.youtube.com/watch?v=6EzMdAskU9M
*   
*	New BSD License
*	https://www.vutbr.cz/studis/student.phtml?gm=gm_detail_predmetu&apid=158780
*
*	C language is all about speed. Hot, nasty, bad-ass speed. - Eleanor Roosevelt, 1936.
*/

#pragma once
#include <iostream>
#include <string>
#include <vector>
//#include <mutex>
//#include <future>
//#include <atomic>
#include <iomanip>
#include <algorithm>
//#include <memory>


const size_t NON_EDGE = std::numeric_limits<size_t>::max();

typedef struct Vertex
{
    size_t  idx;    // 0-X
    size_t  value;  // pro dijkstruv algoritmus
    size_t  pred;

    Vertex()
    {
        idx = 0;
        value = pred = 0;
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
    os << v.idx ;
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


template <class V, class E> class Graph
{
public:

    explicit Graph(const size_t size, const bool directed = false)
    {
        try
        {
            m_size = size;
            m_directed = directed;

            m_vertices.reserve(size);
            m_edges.reserve(size);
            
            m_matrix.resize(size, std::vector<bool>(size));
            m_edgeMatrix.resize(size, std::vector<size_t>(size, NON_EDGE));
        }
        catch (std::bad_alloc& e)
        {
            std::cerr << e.what() << "\n";
            throw;
        }
    };

    virtual ~Graph()
    {
        makeEmpty();
    };

    void makeEmpty()
    {
        m_matrix.clear();
        m_edgeMatrix.clear();
        m_directed = false;

        // vymazeme vsechny ptr
        m_vertices.clear();

        // uvolnime ptr na hrany
        for (auto i : m_edges)
            if (i) delete i;
    };

    void addVertex(const V v)
    {
        if (vertexExists(v))
            throw std::logic_error("Vertex exists!\n");

        static size_t it;

        if ((it) >= m_vertices.capacity())
            throw std::logic_error("Maximum capacity reached!\n");

        m_vertices.push_back(v);
    };

    void addEdge(const V from, const V to, E* edge)
    {
        try
        {
            const size_t x = getVertexIndex(from);
            const size_t y = getVertexIndex(to);

            addEdge(x, y, edge);
        }
        catch (std::invalid_argument& e)
        {
            std::cerr << e.what();
            throw std::invalid_argument("Cannot add edge!\n");
        }
    };

    void addEdge(const size_t from, const size_t to, E* edge)
    {
        // pridani hrany do grafu, nejprve se provede bounds check a
        // dale je zjisten stav hrany tj. zda je hrana nullptr nebo ne
        // + pokud hrana existuje zjisti se edgeID a nasleduje zjisteni
        // zda je graf smerovy (directed) nebo ne,
        // + v pripade smeroveho grafu je oznaceno v maticich ze je
        // mezi uzly hrana a tato hrana je pridana do vektoru hran
        // - v pripade ze graf je nesmerovy je oznaceno v maticich take
        // ze hrany existuji i v opacnem smeru

        if ((from >= m_size) || (to >= m_size))
        {

            std::cout << m_size << "\n";
            std::cout << from << "\n";
            std::cout << to << "\n";

            throw std::invalid_argument("Out of bounds!\n");
        }

        const bool edgeState = (edge) ? true : false;
        const auto edgeID = edgeState ? m_edges.size() : NON_EDGE;

        if (m_directed)
        {
            if (edgeState)
                m_edges.push_back(edge);

            m_matrix[from][to] = edgeState;
            m_edgeMatrix[from][to] = edgeID;
        }
        else
        {
            if (m_edgeMatrix[to][from] == NON_EDGE)
            {
                if (edgeState)
                    m_edges.push_back(edge);

                m_matrix[from][to] = edgeState;
                m_edgeMatrix[from][to] = edgeID;

                m_matrix[to][from] = edgeState;
                m_edgeMatrix[to][from] = edgeID;
            }
        }
    };

    V* getVertex(const size_t idx)
    {
        if (idx >= m_size)
            throw std::invalid_argument("Out of bounds!\n");

        return &m_vertices[idx];
    }

    E* getEdge(const size_t idx) const
    {
        if (idx >= m_edges.size())
            throw std::invalid_argument("Out of bounds!\n");

        return m_edges[idx];
    }

    E* getEdge(const size_t from, const size_t to) const
    {
        if ((from >= m_size) && (to >= m_size))
            throw std::invalid_argument("Out of bounds!\n");

        if (m_edgeMatrix[from][to] == NON_EDGE)
            throw std::runtime_error("Cannot acces NON_EDGE!\n");

        return getEdge(m_edgeMatrix[from][to]);
    }

    E* getEdge(const V* from, const V* to) const
    {
        if ((from->idx >= m_size) && (to->idx >= m_size))
            throw std::invalid_argument("Out of bounds!\n");

        return getEdge(m_edgeMatrix[from->idx][to->idx]);
    }

    size_t getEdgesCount() const
    {
        return m_edges.size();
    };

    size_t getVertexCount() const
    {
        return m_vertices.size();
    };

    size_t getVertexIndex(V* v) const
    {
        auto p = std::find_if(m_vertices.begin(), m_vertices.end(), [&](V n)
                              {
                                  return *v == n;
                              });

        if (p != m_vertices.end())
            return std::distance(m_vertices.begin(), p);
        else
            throw std::invalid_argument("Vertex not found!\n");
    }

    std::vector<std::pair<size_t, size_t>> getAdjecent(const size_t from) const
    {
        // pro dany uzel projdeme matici sousednosti a  v pripade ze je dany
        // uzel
        // propojen s dalsim uzlem hranou je ID tohoto uzlu a ID hrany ulozeno
        // do vektoru obsahujici std::pair <ID uzlu , ID hrany>

        // if (from >= m_size)
        //    throw std::invalid_argument("Out of bounds!\n");

        std::vector<std::pair<size_t, size_t>> pom;
        pom.reserve(m_size);

        for (size_t i = 0; i < m_size; ++i)
        {
            if (m_matrix[from][i])
            {
                // size_t id = m_edgeMatrix[from][i];
                // pom.push_back(std::make_pair(i, id));
                pom.push_back(std::make_pair(i, m_edgeMatrix[from][i]));
            }
        }

        return pom;
    }

    std::vector<std::pair<size_t, size_t>> getAdjecent(V* v) const
    {
        return getAdjecent(getVertexIndex(v));
    }

    bool isConnected(const V from, const V to) const
    {
        size_t x = getVertexIndex(from);
        size_t y = getVertexIndex(to);

        return m_matrix[x][y];
    }

    bool isConnected(const size_t from, const size_t to) const
    {
        if (from >= m_size || to >= m_size)
            throw std::invalid_argument("Out of bounds!\n");

        return m_matrix[from][to];
    }

    void printMatrix()
    {
        std::cout << "\nBool matrix\n";
        std::cout << "- ";

        for (size_t i = 0; i < m_size - 1; ++i)
            std::cout << "|" << std::setw(2) << i;

        std::cout << "|" << std::setw(2) << m_size << "\n";

        int i = 0;
        for (const auto& v : m_matrix)
        {
            std::cout << std::setw(2) << i++ << "|";

            for (size_t j = 0; j < v.size() - 1; ++j)
                v[j] ? std::cout << std::setw(2) << 1 << "|"
                     : std::cout << std::setw(2) << 0 << "|";

            v[v.size() - 1] ? std::cout << std::setw(2) << 1 << "\n"
                            : std::cout << std::setw(2) << 0 << "\n";
        }
    }

    void printEdgeMatrix()
    {
        std::cout << "\nEdge index matrix\n";
        std::cout << "-";

        for (size_t i = 0; i < m_size - 1; ++i)
            std::cout << "|" << std::setw(5) << i;
        std::cout << "|" << std::setw(5) << m_size << "\n";

        int i = 0;
        for (const auto& v : m_edgeMatrix)
        {
            std::cout << i++ << "|";

            for (size_t j = 0; j < v.size() - 1; ++j)
            {
                if (v[j] != NON_EDGE)
                    std::cout << std::setw(5) << v[j] << "|";
                else
                    std::cout << std::setw(5) << "N"
                              << "|";
            }

            if (v[v.size() - 1] != NON_EDGE)
                std::cout << std::setw(5) << v[v.size() - 1] << "\n";
            else
                std::cout << std::setw(5) << "N"
                          << "\n";
        }
    }

    void printDistMatrix()
    {
        std::cout << "\nDistance matrix\n";
        std::cout << "-";

        for (size_t i = 0; i < m_size - 1; ++i)
            std::cout << "|" << std::setw(5) << i;
        std::cout << "|" << std::setw(5) << m_size - 1 << "\n";

        int i = 0;
        for (const auto& v : m_edgeMatrix)
        {
            std::cout << i++ << "|";
            size_t id = 0;

            for (size_t j = 0; j < v.size() - 1; ++j)
            {
                id = v[j];
                if (id != NON_EDGE)
                    std::cout << std::setw(5) << *m_edges[id] << "|";
                else
                    std::cout << std::setw(5) << 0 << "|";
            }
            id = v[v.size() - 1];
            if (id != NON_EDGE)
                std::cout << std::setw(5) << *m_edges[id] << "\n";
            else
                std::cout << std::setw(5) << 0 << "\n";
        }
    }
    
    void printVertices()
    {
        for (const auto& v : m_vertices)
            std::cout << v << "\n";
    }

  protected:

    bool vertexExists(V v)
    {
        auto p =
            std::find_if(m_vertices.begin(), m_vertices.end(), [&v](V const& n)
                         {
                             return v == n;
                         });

        // vertex not found
        if (p == m_vertices.end())
            return false;

        return true;
    }

     Graph() = delete;

  public:
    size_t m_size;
    bool   m_directed;

    std::vector<std::vector<bool>>   m_matrix;
    std::vector<std::vector<size_t>> m_edgeMatrix;

    std::vector<E*> m_edges;
    std::vector<V>  m_vertices;
};
