# binary tree
# https://www.cs.cmu.edu/~adamchik/15-121/lectures/Trees/trees.html
# http://www.openbookproject.net/thinkcs/archive/java/english/chap17.htm

import queue
import stack


class Node:

    def __init__(self, data_):
        self.__data = data_
        self.__left = None
        self.__right = None

    def getData(self):
        return self.__data

    def setData(self, data_):
        self.__data = data_

    def getLeft(self):
        return self.__left

    def getRight(self):
        return self.__right

    def setLeft(self, node):
        self.__left = node

    def setRight(self, node):
        self.__right = node


class BTree:

    def __init__(self):
        pass

    def insert(self, data, parent=None):
        node = Node(data)

        if parent == None:
            return node
        else:
            if data < parent.getData():
                parent.setLeft(node)
            else:
                parent.setRight(node)

        return node

    # Prochazeni stromu a hledani
    # Mame dve metody DFS (do hloubky) a BFS (do sirky).
    # U DFS mame nekolik zpusobou jak budeme budeme postupovat stromem.

    # DFS traversing, recursive
    def dfs_traverse_pre_order(self, node):
        '''
            Navštívíme vrchol a potom levý a pravý podstrom
        '''
        if node != None:
            print(node.getData())
            self.dfs_traverse_pre_order(node.getLeft())
            self.dfs_traverse_pre_order(node.getRight())

    def dfs_traverse_in_order(self, node):
        '''
            Navštívíme levý podstrom, vrchol a pravý podstrom.
        '''
        if node != None:
            self.dfs_traverse_in_order(node.getLeft())
            print(node.getData())
            self.dfs_traverse_in_order(node.getRight())

    def dfs_traverse_post_order(self, node):
        '''
            Navštívíme levý a pravý podstrom a potom vrchol
        '''
        if node != None:
            self.dfs_traverse_post_order(node.getLeft())
            self.dfs_traverse_post_order(node.getRight())
            print(node.getData())

    # DFS traversing, non recursive
    # https://en.wikipedia.org/wiki/Depth-first_search
    def dfs_traverse(self, root):
        lifo = stack.Stack()
        lifo.push(root)

        while not lifo.isEmpty():
            node = lifo.pop()

            if node != None:
                print(node.getData())
                lifo.push(node.getLeft())
                lifo.push(node.getRight())

    # BFS traversing
    # https://en.wikipedia.org/wiki/Breadth-first_search
    def bfs_traverse(self, node):
        fifo = queue.Queue()
        fifo.push(node)

        while not fifo.isEmpty():
            n = fifo.pop()

            if n != None:
                print(n.getData())
                fifo.push(n.getLeft())
                fifo.push(n.getRight())

    # breath first search
    def search_bfs(self, root, nodeToFind):
        '''
            Prochazime strom do sirky a hledame pozadovany uzel.
            Nerekurzivni funkce za pouziti fronty.
        '''
        fifo = queue.Queue()
        fifo.push(root)

        while not fifo.isEmpty():
            node = fifo.pop()

            if node != None:
                print(node.getData())

                if node == nodeToFind:
                    return node
                else:
                    fifo.push(node.getLeft())
                    fifo.push(node.getRight())

    # depth first search
    def search_dfs(self, root, nodeToFind):
        '''
            Prochazime strom do hloubky a hledame pozadovany uzel.
            Nerekurzivni funkce za pouziti zasobniku.
        '''
        lifo = stack.Stack()
        lifo.push(root)

        while not lifo.isEmpty():
            node = lifo.pop()

            if node != None:
                if node == nodeToFind:
                    return node
                else:
                    lifo.push(node.getLeft())
                    lifo.push(node.getRight())


    # funkce ktera nam najde nejvetsi hodnotu (tj. lezi co nejvic v pravo)
    # v dane vetvi stromu
    def findHighestValue(self, node):

        while node.getRight() is not None:
            node = node.getRight()

        return node.getData()

    # vymazeme danou hodnotu ze stromu
    def delete(self, node, toDelete):

        if node == None:
            return None

        if toDelete < node.getData():
            node.setLeft(self.delete(node.getLeft(), toDelete))
        elif toDelete > node.getData():
            node.setRight(self.delete(node.getRight(), toDelete))

        else:

            if node.getLeft() == None:
                temp = node.getRight()
                del node
                return temp

            elif node.getRight() == None:
                temp = node.getLeft()
                del node
                return temp

            else:
                # najdeme hodnotu, ktera je co nejvetsi
                # (tj. lezi co co nejvic v pravo) ktera je v leve vetvi
                node.setData(self.retData(node.getLeft()))
                # a nastavime ji jako novou hodnotu pro node (kokren vetve)
                # + odstranime ji samozrejme z te puvodniho mista
                node.setLeft(self.delete(node.getLeft(), node.getData()))

        return node

    # hezci tisk stromu
    def print(self, root):
        currLevel = [root]

        while currLevel:
            nextLevel = list()

            for n in currLevel:
                print(n.getData(), end=' '),
                if n.getLeft():
                    nextLevel.append(n.getLeft())
                if n.getRight():
                    nextLevel.append(n.getRight())

            print()
            currLevel = nextLevel

####################

# Tree
#            8
#           / \
#          3   9
#         / \   \
#        1   5   12
#           /    /
#          4    11

root = None
tree = BTree()
root = tree.insert(8, root)

# left part of tree
l = tree.insert(3, root)
tree.insert(1, l)
r = tree.insert(5, l)
tree.insert(4, r)

# right part of tree
r = tree.insert(9, root)
r = tree.insert(12, r)
toFind = tree.insert(11, r)

# prochazeni
# tree.dfs_traverse_pre_order(root)
# tree.dfs_traverse_in_order(root)
# tree.dfs_traverse_post_order(root)
# tree.dfs_traverse(root)
# tree.bfs_traverse(root)

# hledani
# tree.search_bfs(root, toFind)
# tree.search_dfs(root, toFind)

tree.dfs_traverse_pre_order(root)
root = tree.delete(root, 5)
# root = tree.delete(root, 8)

print('-----------------')
# tree.dfs_traverse_pre_order(root)

tree.print(root)
