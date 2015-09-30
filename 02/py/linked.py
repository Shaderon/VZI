# linked list

class Node:
    def __init__(self, data_):
        self.data = data_
        self.next = None
        self.pred = None

    def getData(self):
        return self.data

    def setNext(self,newNext):
        self.next = newNext

    def setPred(self,newPred):
        self.pred = newPred

    def getNext(self):
        return self.next

    def getPred(self):
        return self.pred


class DoubleLinkedList:

    def __init__(self):
        self.head = None
        self.last = None
        self.size = 0

    def isEmpty(self):
        return self.head == None

    def pushBack(self, item):
        temp = Node(item)
        self.size += 1

        if self.isEmpty():
            self.head = temp
            self.last = self.head
        else:
            self.last.setNext(temp)
            temp.setPred(self.last)
            temp.setNext(None)
            self.last = temp

    def printList(self):
        current = self.head

        while(current is not None):
            print(current.getData())
            current = current.getNext()

    def printListBackWard(self):
        current = self.last

        while(current is not None):
            print(current.getData())
            current = current.getPred()

    def remove(self, idx):
        if idx >= self.size:
            return
        else:
            curr = self.head

            for i in range(idx):
                curr = curr.getNext()

            # node je last
            if curr.getNext() is None:
                curr.getPred().setNext(None)
                self.last = curr.getPred()
            # node je head
            elif curr is self.head:
                temp = curr.getNext()
                temp.setPred(None)
                self.head = temp
            else:
                curr.getPred().setNext(curr.getNext())
                curr.getNext().setPred(curr.getPred())


# main()

lst = DoubleLinkedList()

lst.pushBack(1)
lst.pushBack(2)
lst.pushBack(3)

lst.printList()
# lst.printListBackWard()

lst.remove(2)

lst.printList()


