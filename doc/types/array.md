# Array 

The array type is used store a dynamic array of elements of any type.

## Member Functions

### -> size(): int

Return the size the array as an int;

### -> is_empty(): bool

Returns wether the array is empty (size == 0)

### -> push(value): null

Append a single value to the end of the array

### -> pop()

Remove a single value from the end the array.  
The removed value is returned.  
Throws an exception if the array is empty.

### -> front()

Return the value at index 0.  
Throws an exception if the array is empty.

### -> back()

Return the value at the end of the array.  
Throws an exception if the array is empty.

### -> peek()

Return the value at the end of the array.  
Throws an exception if the array is empty.

### -> at(index : int)

Returns the value at the given index.  
Throws an exception if the array is empty or the index is out of range.


### -> insert(index : int, value): null

Inserts a value at the given index.  
Throws an exception if the array is empty or the index is out of range.


### -> erase(index : int)

Erases the value at the given index.
The removed value is returned.  
Throws an exception if the array is empty or the index is out of range.



## Operators

### [index : int]

Returns the value at the given index. 
Throws an exception if the array is empty or the index is out of range.




## Literal

A new array can be create by writing a comma separated list between `[` and `]` e.g. `[1, 2, 3,]` or `[42, 42]`. 
A single trailing comma is allowed.

Example:
```js
function main() {
	var array = [1, 2, 3,];
	std::println(array);
}
```