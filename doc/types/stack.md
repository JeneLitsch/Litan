# Stack

A LIFO data structure

## Member Functions

### -> size(): Int

Returns the number elements on the stack.

### -> is_empty(): Bool

Returns whether the stack is empty (size == 0).

### -> push()

Adds an element to the top of the stack.

### -> pop(): Any

Removes and returns an element from the top of the stack.  
If called on an empty stack an exception is thrown.

### -> values(): Array

Copies the values on the stack into an array and returns it.  
Index 0 corresponds to the bottom of the stack.
