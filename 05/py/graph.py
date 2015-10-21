# basic graph using dictionary

class Edge:

    def __init__(self, input, output, weight):
        self.input  = input
        self.output = output
        self.weight = weight


class Graph:

    def __init__(self, g = {}):
        self.__graph = g

    def addVertex(self, v):
        if v not in self.__graph:
            self.__graph[v] = list()

    def addEdge(self, edge):

        if edge.input in self.__graph:
            self.__graph[edge.input].append(edge)
        else:
            self.__graph[edge.input] = [edge]

    def getVertices(self):
        return list(self.__graph.keys())

    def getEdges(self, v):
        return list(self.__graph[v])


###
# Graph
#
#       1 *---* 3
#     * *       * \
#    /  |       |  *
#   0   |       |   5
#    \  |       |  *
#     * *       * /
#       2 *---* 4
#

g = Graph()

g.addVertex(0)
g.addVertex(1)
g.addVertex(2)
g.addVertex(3)
g.addVertex(4)
g.addVertex(5)

g.addEdge(Edge(0, 1, 1))
g.addEdge(Edge(0, 2, 1))
g.addEdge(Edge(1, 2, 1))
g.addEdge(Edge(1, 3, 1))
g.addEdge(Edge(2, 1, 1))
g.addEdge(Edge(2, 4, 1))
g.addEdge(Edge(3, 4, 1))
g.addEdge(Edge(3, 5, 1))
g.addEdge(Edge(4, 3, 1))
g.addEdge(Edge(4, 5, 1))


print(g.getVertices())

edges = g.getEdges(0)
print([e.weight for e in edges])



