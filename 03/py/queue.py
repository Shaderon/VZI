# implementace adt FIFO neboli Queue

class Node:

    def __init__(self, data_):
        self.data = data_
        self.next = None
        self.pred = None

    def getData(self):
        return self.data

    def setNext(self, newNext):
        self.next = newNext

    def setPred(self, newPred):
        self.pred = newPred

    def getNext(self):
        return self.next

    def getPred(self):
        return self.pred


class Fifo:

    def __init__(self):
        self.head = None
        self.last = None
        self.size = 0

    def isEmpty(self):
        return self.head == None

    def push(self, item):
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

    def pop(self):
        if self.size <= 0:
            raise Exception('Stack is empty!')
        else:
            data = self.head.data
            tmp = self.head

            if(self.size > 1):
                tmp.getNext().setPred(None)
                self.head = tmp.getNext()
            else:
                self.head = None

            self.size -= 1
            return data

    def print(self):
        current = self.head

        while(current is not None):
            print(current.getData())
            current = current.getNext()


st = Fifo()

st.push("Ahoj!")
st.push("Nazdar!")
st.push("Cau!")

st.print()

print("--------")
print(st.pop())
print(st.pop())
print(st.pop())

print("--------")
try:
    print(st.pop())
except Exception as msg:
    print(msg)
