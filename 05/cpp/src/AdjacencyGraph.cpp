#include "AdjacencyGraph.h"

void AdjecencyGraph::makeEmpty()
{
    m_matrix.clear();
    m_edgeMatrix.clear();
    m_directed = false;

    // vymazeme vsechny ptr
    m_vertices.clear();

    // uvolnime ptr na hrany
    for (auto i : m_edges)
        if (i)
            delete i;
}

bool AdjecencyGraph::vertexExists(const Vertex& v)
{
    auto p =
        std::find_if(m_vertices.begin(), m_vertices.end(), [&v](Vertex const& n)
                     {
                         return v == n;
                     });

    // vertex not found
    if (p == m_vertices.end())
        return false;

    return true;
}

AdjecencyGraph::AdjecencyGraph(const size_t size, const bool directed)
    : IGraph(size, directed)
{
    try
    {
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
}

AdjecencyGraph::~AdjecencyGraph()
{
    makeEmpty();
}

void AdjecencyGraph::addVertex(const Vertex& v)
{
    if (vertexExists(v))
        throw std::logic_error("Vertex exists!\n");

    static size_t it;

    if ((it) >= m_vertices.capacity())
        throw std::logic_error("Maximum capacity reached!\n");

    m_vertices.push_back(v);
}

void AdjecencyGraph::addEdge(const size_t from, const size_t to, size_t dist)
{
    if ((from >= m_size) || (to >= m_size))
    {

        std::cout << m_size << "\n";
        std::cout << from << "\n";
        std::cout << to << "\n";

        throw std::invalid_argument("Out of bounds!\n");
    }

    try
    {
        const auto edgeID = m_edges.size();

        auto* edge = new (Edge);
        edge->idx = edgeID;
        edge->distance = dist;

        if (m_directed)
        {
            m_edges.push_back(edge);

            m_matrix[from][to] = true;
            m_edgeMatrix[from][to] = edgeID;
        }
        else
        {
            if (m_edgeMatrix[to][from] == NON_EDGE)
            {
                m_edges.push_back(edge);
                m_matrix[from][to] = true;
                m_edgeMatrix[from][to] = edgeID;

                m_matrix[to][from] = true;
                m_edgeMatrix[to][from] = edgeID;
            }
        }
    }
    catch (std::exception& e)
    {
        std::cerr << e.what() << "\n";
        throw;
    }
}

Vertex* AdjecencyGraph::getVertex(const size_t idx)
{
    if (idx >= m_size)
        throw std::invalid_argument("Out of bounds!\n");

    return &m_vertices[idx];
}

Edge* AdjecencyGraph::getEdge(const size_t idx)
{
    if (idx >= m_edges.size())
        throw std::invalid_argument("Out of bounds!\n");

    return m_edges[idx];
}

Edge* AdjecencyGraph::getEdge(const size_t from, const size_t to)
{
    if ((from >= m_size) && (to >= m_size))
        throw std::invalid_argument("Out of bounds!\n");

    if (m_edgeMatrix[from][to] == NON_EDGE)
        throw std::runtime_error("Cannot acces NON_EDGE!\n");

    return getEdge(m_edgeMatrix[from][to]);
}

size_t AdjecencyGraph::getEdgesCount()
{
    return m_edges.size();
}

size_t AdjecencyGraph::getVertexCount()
{
    return m_vertices.size();
}

std::vector<std::pair<size_t, size_t>>
    AdjecencyGraph::getAdjecent(const size_t from)
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

bool AdjecencyGraph::isConnected(const size_t from, const size_t to)
{
    if (from >= m_size || to >= m_size)
        throw std::invalid_argument("Out of bounds!\n");

    return m_matrix[from][to];
}

void AdjecencyGraph::printMatrix()
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

void AdjecencyGraph::printEdgeMatrix()
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

void AdjecencyGraph::printDistMatrix()
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

void AdjecencyGraph::printVertices()
{
    for (const auto& v : m_vertices)
        std::cout << v << "\n";
}
