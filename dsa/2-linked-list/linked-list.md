## linked list
```py
class LinkedList:
	def __init__(self, node = None):
		self.length = 0
		self.head = node

class Node:
	def __init__(self, data = None, next = None):
		self.data = data
		self.next = next


def insertAtBeginning(self, data):
	newNode = Node()
	newNode.data = data
	if self.head == None:
		self.head = newNode
	else:
		newNode.next = self.head
		self.head = newNode

def insertAtEnd(self, data):
	newNode = Node(data)
	if self.head == None:
		self.head = newNode
		return
	current = self.head
	while current.next != None:
		current = current.next
		curent.next = newNode

def insertAtGivenPosition(self, pos, data):
	newNode = Node(data)
	if pos == 0:
		newNode.next = self.head
		self.head = newNode
		return
	
	currPos = 1
	current = self.head
	while currPos < pos-1 and current.next != None:
		current = current.next
		currPos += 1
	newNode.next = current.next
	current.next = newNode 
```


### reverse linked list
```python
def reverseLinkedList(head):
	prevNode, currNode = None, head
	while currNode != None:
		nextNode = currNode.next
		currNode.next = prevNode
		prevNode = currNode
		currNode = nextNode
	return prevNode
```