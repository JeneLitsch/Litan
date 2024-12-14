# Queue

A FIFO data structure

## Member Functions

### ->size(): Int

Returns the number elements in the queue.

### ->is_empty(): Bool

Returns whether the queue is empty (size == 0).

### ->push()

Adds an element to the end of the queue.

### ->pop(): Any

Removes and returns an element from the front of the queue.  
If called on an empty queue an exception is thrown.

### ->values():Array

Copies the values from the queue into an array and returns it.  
Index 0 corresponds to the front of the queue.
