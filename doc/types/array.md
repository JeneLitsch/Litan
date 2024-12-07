# Array 

The array type is used store a dynamic array of elements of any type.

## Member Functions

### -> size(): Int

Return the size the array as an int;

### -> is_empty(): Bool

Returns wether the array is empty (size == 0)

### -> push(value : Any): Null

Append a single value to the end of the array

### -> pop(): Any

Remove a single value from the end the array.  
The removed value is returned.  
Throws an exception if the array is empty.

### -> front(): Any

Return the value at index 0.  
Throws an exception if the array is empty.

### -> back(): Any

Return the value at the end of the array.  
Throws an exception if the array is empty.

### -> peek(): Any

Return the value at the end of the array.  
Throws an exception if the array is empty.

### -> at(index : Int): Any

Returns the value at the given index.  
Throws an exception if the array is empty or the index is out of range.


### -> insert(index : Int, value): Null

Inserts a value at the given index.  
Throws an exception if the array is empty or the index is out of range.


### -> erase(index : Int): Any

Erases the value at the given index.
The removed value is returned.  
Throws an exception if the array is empty or the index is out of range.


### -> filter(f : Function): Array

Creates a shallow copy containing the elements for which `f` returns a truthy result.


### -> transform(f : Function): Array

Calls `f` for all elements and create an array containing the result.


### -> reduce(f : Function): Any

Sums up all elements using `f`.
Returns `null` if the array is empty.



## Operators

### [index : int]

Returns the value at the given index. 
Throws an exception if the array is empty or the index is out of range.

### array + array

Concatenate two arrays.

### array * int

Repeat an array.

### int * array

Repeat an array.



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