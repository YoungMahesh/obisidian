### Pointers(`*`)
- In CPP, a pointer is a variable that holds the memory address of another variable.
- Pointers are declared using the asterix symbol (`*`) before the pointer name

### Member Access Operator (`->`)
- The arrow operator (`->`) is used to access members (methods or variables) of a struct or class through a pointer

### Deference Operator
- The asterix symbol (`*`) is also used as the dereference operator, which returns the "value" stored at memory address held by a pointer

### example
```cpp
ListNode *currNode = head; // both currNode and head are pointers
currNode->val; // get value of currNode object
&currNode->val; // get address of val

(*currNode).val == currNode->val
```

### struct, class, object
- struct: data type to group variables of different data types together
- class: data type to group variables and functions together
- object: an instance of a class
