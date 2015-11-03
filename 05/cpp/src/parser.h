#pragma once

#include <vector>
#include <string>
#include <memory>
#include <regex>
#include <fstream>
#include <exception>
#include <sstream>

#include "GraphDef.h"

// Parser pro soubory obsahujici zadani grafu,
// tento soubor je rozdelen do casti kteym odpovida podoba structu Problem
// ukazka takovehoto souboru>
// 
//    NAME: Matousek6
//    COMMENT : Fun with graphs!
//    GRAPH : UNDIRECTED
//    DIMENSION : 6
//    EDGE_DIRECTIONS_SECTION
//    2 3           // uzel cislo 1 ma hrany ktere vedou do uzlu 2 a 3
//    1 3 4
//    1 2 5
//    2 5 6
//    3 4 6
//    4 5
//    EDGE_WEIGHT_SECTION
//    10 10        // ohodnoceni pro hrany ktere vedou z uzlu 1 do uzlu 2 a 3
//    10 10 10
//    10 10 10
//    10 10 10
//    10 10 10
//    10 10


typedef struct Problem
{
    std::string                      name;      // nazev grafu 
    std::vector<std::string>         comment;   // pripadny komentar ke grafu
    size_t                           dimension; // velikost grafu
    bool                             directed;  // je graf orientovany or not?
    std::vector<std::vector<size_t>> edgeList;  // kazdy radek obsahuje do ktereho uzlu 
                                                // vede hrana z daneho uzlu (prvni radek v teto sekci je prvni uzel)
    std::vector<std::vector<size_t>> weightList;// to same co predchozi jen obsahuje ohodnoceni dane hrany

} Problem_t;

class GraphParser
{
    
  public:
    GraphParser()
    { }

    ~GraphParser()
    {
        m_buffer.clear();
    }

    void parse(const std::string inputFile, Problem_t& problem);

  private:

    const std::string ERR = "An error occurred in parsing map file! \n";

    void readFile(const std::string inputFile);
    void sanitizeBuffer();
    bool hasOnlySpaces(const std::string& str);
    template <class T> T convert(std::string const& str);
    template <typename T> std::vector<T> split(const T& str, const T& delimiters);
    std::string searchForItem(const std::regex r);
    bool isValueString(const std::string& str);

    std::string parseName();;
    void parseComment(std::vector<std::string>& commentary);;
    size_t parseDimension();;
    bool parseGraphDirection();
    void parseEdgesList(std::vector<std::vector<size_t>>& edges);
    void parseWeightList(std::vector<std::vector<size_t>>& weights);

  private:
    std::vector<std::string> m_buffer;
};