# binary search tree
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
        # pass
        self.root = None

    def getRoot(self):
        return self.root

    def insert(self, data):
        self.root = self.insert_data(self.root, data)

        return self.root

    def insert_data(self, parent, data):

        if parent == None:
            node = Node(data)
            return node

        if data == parent.getData():
            return parent

        if data < parent.getData():
            parent.setLeft(self.insert_data(parent.getLeft(), data))
        else:
            parent.setRight(self.insert_data(parent.getRight(), data))

        return parent


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
    # def dfs_traverse(self, root):
    def dfs_traverse(self):
        lifo = stack.Stack()
        lifo.push(self.root)

        while not lifo.isEmpty():
            node = lifo.pop()

            if node != None:
                print(node.getData())
                lifo.push(node.getLeft())
                lifo.push(node.getRight())

    # BFS traversing
    # https://en.wikipedia.org/wiki/Breadth-first_search
    def bfs_traverse(self):
    # def bfs_traverse(self, node):
        fifo = queue.Queue()
        fifo.push(self.root)

        while not fifo.isEmpty():
            n = fifo.pop()

            if n != None:
                print(n.getData())
                fifo.push(n.getLeft())
                fifo.push(n.getRight())

    # breath first search
    def search_bfs(self, data):
        '''
            Prochazime strom do sirky a hledame pozadovany uzel.
            Nerekurzivni funkce za pouziti fronty.
        '''
        fifo = queue.Queue()
        fifo.push(self.root)

        while not fifo.isEmpty():
            node = fifo.pop()

            if node != None:
                # print(node.getData())

                if node.getData() == data:
                    return node
                else:
                    fifo.push(node.getLeft())
                    fifo.push(node.getRight())

    # depth first search
    # def search_dfs(self, root, data):
    def search_dfs(self, data):
        '''
            Prochazime strom do hloubky a hledame pozadovany uzel.
            Nerekurzivni funkce za pouziti zasobniku.
        '''
        lifo = stack.Stack()
        lifo.push(self.root)

        while not lifo.isEmpty():
            node = lifo.pop()

            if node != None:
                if node.getData() == data:
                    return node
                else:
                    lifo.push(node.getLeft())
                    lifo.push(node.getRight())


    # mazani uzlu obsahujici dane data
    def delete(self, data):
        self.root = self.delete_data(self.root, data)

        return self.root

    # funkce ktera nam najde nejvetsi hodnotu (tj. lezi co nejvic v pravo)
    # na leve strane stromu

    def retrieveData(self, node):

        while node.getRight() is not None:
            node = node.getRight()

        return node.getData()

    # vymazeme danou hodnotu ze stromu
    def delete_data(self, parent, toDelete):

        if toDelete < parent.getData():
            parent.setLeft(self.delete_data(parent.getLeft(), toDelete))
        elif toDelete > parent.getData():
            parent.setRight(self.delete_data(parent.getRight(), toDelete))

        else:

            if parent.getLeft() == None:
                temp = parent.getRight()
                del parent
                return temp

            elif parent.getRight() == None:
                temp = parent.getLeft()
                del parent
                return temp

            else:
                # najdeme hodnotu, ktera je co nejvetsi
                # (tj. lezi co co nejvic v pravo) ktera je v leve vetvi
                parent.setData(self.retrieveData(parent.getLeft()))

                # a nastavime ji jako novou hodnotu pro parent (kokren vetve)
                # + odstranime ji samozrejme z te puvodniho mista
                parent.setLeft(self.delete_data(parent.getLeft(), parent.getData()))

        return parent

    # hezci tisk stromu
    def print(self):
        currLevel = [self.root]

        if self.root == None:
            return

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

tree.insert(8)
tree.insert(3)
tree.insert(1)
tree.insert(5)
tree.insert(4)
tree.insert(9)
tree.insert(12)
tree.insert(11)

tree.print()
print('-----------------')

# prochazeni
tree.dfs_traverse_pre_order(tree.getRoot())
# tree.dfs_traverse_in_order(tree.getRoot())
# tree.dfs_traverse_post_order(tree.getRoot())

# tree.bfs_traverse()
# tree.dfs_traverse()

# hledani

# node = tree.search_bfs(root, 4)
# print(node.getData())

# node = tree.search_dfs(root, 11)
# print(node.getData())

# print(tree.search_bfs(5).getData())
# print(tree.search_dfs(5).getData())

#mazani
# root = tree.delete(5)
# root = tree.delete(8)

print('-----------------')
tree.print()

