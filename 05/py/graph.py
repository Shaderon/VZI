# basic graph using dictionary
# http://kam.mff.cuni.cz/~kuba/ka/reprezentace_grafu.pdf
# https://en.wikipedia.org/wiki/Dijkstra's_algorithm

import sys
import queue # pouzijeme priority queue

INFINITY = sys.maxsize

class Edge:

    def __init__(self, input, output, distance):
        self.input  = input
        self.output = output
        self.distance = distance


class Vertex:

    def __init__(self, id):
        self.id = id
        self.adjecent = {} # dictionary sousednich uzlu

        # pro dijkstruv algoritmus
        self.dist     = 0
        self.visited  = False
        self.previous = None


class Graph:

    def __init__(self, directed):
        self.graph    = {}
        self.directed = directed

    def addVertex(self, vertexId):
        if vertexId not in self.graph:
            node = Vertex(vertexId)
            self.graph[vertexId] = node

    def getVertex(self, vertexId):
        if vertexId in self.graph:
            return self.graph[vertexId]
        else:
            return None

    def getVerticesIds(self):
        return list(self.graph.keys())

    def getAdjecent(self, vertexId):
        return list(self.graph[vertexId].adjecent)

    def addEdge(self, frm, to, w):

        e = Edge(frm, to, w)

        if frm in self.graph and to in self.graph:
            if self.directed:
                self.graph[frm].adjecent[to] = e
            else:
                self.graph[frm].adjecent[to] = e
                self.graph[to].adjecent[frm] = e
        else:
            raise Exception('Cannot create new edge!')

    def getEdge(self, frm, to):
        return self.graph[frm].adjecent[to]

    # ----------------------
    def dijkstra(self, startId, endId):

        # init faze
        for i in self.graph.keys():
            self.graph[i].dist     = INFINITY
            self.graph[i].visited  = False
            self.graph[i].previous = None

        self.graph[startId].dist = 0

        open = queue.PriorityQueue()

        for i in self.graph.keys():
            # do prioritni fronty ulozime pair( ohodnoceni uzlu, index uzlu)
            open.put((self.graph[i].dist, i))

        while not open.empty():

            currentNodeId = open.get()[1] # zikame index uzlu s min. hodnotou
            currentNode   = self.graph[currentNodeId]
            currentNode.visited = True

            for i in currentNode.adjecent:
                edgeDistace = self.getEdge(currentNodeId, i).distance
                distance = currentNode.dist + edgeDistace

                if distance < self.graph[i].dist:
                    self.graph[i].dist     = distance
                    self.graph[i].previous = currentNode

        # backtrack
        path = []
        node = self.graph[endId]

        while node != None:
            path.append(node.id)
            node = node.previous

        path.reverse()
        return path

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

g = Graph(True)

g.addVertex(0)
g.addVertex(1)
g.addVertex(2)
g.addVertex(3)
g.addVertex(4)
g.addVertex(5)

g.addEdge(0, 1, 1)
g.addEdge(0, 2, 8)
g.addEdge(1, 2, 2)
g.addEdge(1, 3, 9)
g.addEdge(2, 1, 5)
g.addEdge(2, 4, 3)
g.addEdge(3, 4, 7)
g.addEdge(3, 5, 8)
g.addEdge(4, 3, 6)
g.addEdge(4, 5, 2)

# ziskame ID vsech uzlu
vertices = g.getVerticesIds()
# pomoci techto ID ziskame primo objekt uzlu a vytiskneme jeho id/dist...
print([g.getVertex(v).id for v in vertices])

# pres fci getAdjecent ziskame ID vsech uzlu do kterych smeruji hrany z naseho uzlu
neighbors = g.getAdjecent(0)
print([g.getVertex(n).id for n in neighbors])

# pomoci indexu danych uzlu ziskame hranu
e = g.getEdge(0, 2)
print(e.distance)

# vyhledavani pomoci Dijkstrova algoritmu
path = g.dijkstra(0, 5)
print(path)


