#include "parser.h"

void GraphParser::parse(const std::string inputFile, Problem_t& problem)
{
    m_buffer.clear();

    try
    {
        readFile(inputFile);

        problem.name = parseName();
        parseComment(problem.comment);
        problem.dimension = parseDimension();
        problem.directed = parseGraphDirection();
        parseEdgesList(problem.edgeList);
        parseWeightList(problem.weightList);

    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        throw;
    }
}

void GraphParser::readFile(const std::string inputFile)
{
    std::ifstream f;

    try
    {
        // read TspLib file
        f.open(inputFile, std::ifstream::in);

        if (!f.is_open())
            throw std::runtime_error("Can't open file!");

        while (!f.eof())
        {
            std::string line;
            std::getline(f, line);
            m_buffer.push_back(line);
        }

        f.close();
        sanitizeBuffer();
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        throw;
    }
}

void GraphParser::sanitizeBuffer()
{
    // remove all aempty lines
    for (size_t i = 0; i < m_buffer.size(); ++i)
        if (hasOnlySpaces(m_buffer[i]))
            m_buffer.erase(begin(m_buffer) + i);

    if (m_buffer[m_buffer.size() - 1] != "EOF")
        m_buffer.push_back("EOF");
}

bool GraphParser::hasOnlySpaces(const std::string& str)
{
    return str.find_first_not_of(' ') == str.npos;
}

template <class T>
T GraphParser::convert(std::string const& str) //
{
    std::stringstream os;
    T ret;

    os << str;
    os >> ret;

    return ret;
}

template <typename T> std::vector<T>
GraphParser::split(const T& str, const T& delimiters)
{
    std::vector<T> v;
    size_t start = 0; // T::size_type start = 0;
    auto pos = str.find_first_of(delimiters, start);

    while (pos != T::npos)
    {
        if (pos != start) // ignore empty tokens
            v.emplace_back(str, start, pos - start);
        start = pos + 1;
        pos = str.find_first_of(delimiters, start);
    }

    if (start < str.length()) // ignore trailing delimiter
        v.emplace_back(str, start, str.length() - start);
    // add what's left of the string

    return v;
}

std::string GraphParser::searchForItem(const std::regex r)
{
    std::smatch m;
    const size_t sz = m_buffer.size();
    std::string str;

    for (size_t i = 0; i < sz; ++i)
    {
        if (std::regex_search(m_buffer[i], m, r))
        {
            str = m.suffix();
            break;
        }
    }

    return str;
}

bool GraphParser::isValueString(const std::string& str)
{
    // return str.find_first_not_of("+-. 0123456789") == std::string::npos;
    // if(str.find_first_not_of("+-. 0123456789") == std::string::npos)
    if (str.find_first_of(
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz") !=
        std::string::npos)
        return false;

    return true;
}

std::string GraphParser::parseName()
{
    std::string result;
    const std::regex name("\\s*NAME\\s*:\\s*");
    std::smatch m;

    // first line of TSPlib file is name
    std::regex_search(m_buffer[0], m, name)
        ? result = m.suffix()
        : throw std::runtime_error("Not a TSPLib file!");

    return result;
}

void GraphParser::parseComment(std::vector<std::string>& commentary)
{
    const size_t MAX_SEARCH = 20;
    const std::regex r("\\s*COMMENT\\s*:\\s*");
    std::smatch m;

    // read first 20 lines -> speedup
    size_t sz = MAX_SEARCH > m_buffer.size() ? m_buffer.size() : MAX_SEARCH;

    for (size_t i = 0; i < sz; ++i)
    {
        if (std::regex_search(m_buffer[i], m, r))
        {
            commentary.push_back(m.suffix());
        }
    }
}

size_t GraphParser::parseDimension()
{
    const std::regex r("\\s*DIMENSION\\s*:\\s*");
    const std::string str = searchForItem(r);

    try
    {
        return stoi(str);
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        throw std::runtime_error(ERR);
    }
}

bool GraphParser::parseGraphDirection()
{
    const std::regex dirSection("\\s*GRAPH\\s*:\\s*");
    const std::string dir = "UNDIRECTED";
    bool directed;

    std::string str = searchForItem(dirSection);

    // clean it
    str.erase(remove_if(str.begin(), str.end(), isspace), str.end());

    if (str.compare(dir) == 0)
        directed = false;
    else
        directed = true;

    return directed;
}

void GraphParser::parseEdgesList(std::vector<std::vector<size_t>>& edges)
{
    const std::regex esection("\\s*EDGE_DIRECTIONS_SECTION\\s*");
    const std::regex eos1("\\s*-1\\s*");
    const size_t sz = m_buffer.size();
    size_t i = 0;

    // najdeme header coord section
    while (!regex_match(m_buffer[i++], esection));
    std::vector<std::string> strings;

    for (i; i < sz; ++i)
    {
        if (regex_match(m_buffer[i], eos1) || !isValueString(m_buffer[i]))
            break;

        strings.push_back(m_buffer[i]);
    }

    try
    {
        for (i = 0; i < strings.size(); i++)
        {
            std::vector<std::string> v =
                split<std::string>(strings[i], " ");
            std::vector<size_t> row;

            for (size_t j = 0; j < v.size(); ++j)
                row.push_back(convert<size_t>(v[j]));

            edges.push_back(row);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        throw std::runtime_error(ERR);
    }
}

void GraphParser::parseWeightList(std::vector<std::vector<size_t>>& weights)
{
    const std::regex esection("\\s*EDGE_WEIGHT_SECTION\\s*");
    const std::regex eof("\\s*EOF\\s*");
    const std::regex eos1("\\s*-1\\s*");
    const size_t sz = m_buffer.size();
    size_t i = 0;

    // najdeme header coord section
    while (!regex_match(m_buffer[i++], esection));
    std::vector<std::string> strings;

    for (i; i < sz; ++i)
    {
        if (regex_match(m_buffer[i], eos1) || !isValueString(m_buffer[i]))
            break;

        strings.push_back(m_buffer[i]);
    }

    try
    {
        for (i = 0; i < strings.size(); i++)
        {
            std::vector<std::string> v =
                split<std::string>(strings[i], " ");
            std::vector<size_t> row;

            for (size_t j = 0; j < v.size(); ++j)
                row.push_back(convert<size_t>(v[j]));

            weights.push_back(row);
        }
    }
    catch (const std::exception& e)
    {
        std::cerr << e.what() << "\n";
        throw std::runtime_error(ERR);
    }
}

