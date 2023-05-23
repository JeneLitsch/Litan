# Tuple 

Tuples are fixed sized collections of values with different types. 
A tuple can be created by a comma separated list inside parenthesis.

## Comparison

The elements in the tuple are compared lexikographically. They are compared from left to right. If the lenghts are different it's just a comparison of the lenghts itself.

## Example
```js
function main() {
	var tuple = (1, 2.4, 3); // tuple of type tuple<int, float, int>
	std::println(tuple[0]); // int 0 
	std::println(tuple[1]); // float 2.4
	std::println(tuple[1 + 1]); // any 3
}
```

Use a trailing comma to create single element tuples. 

```js
function main() {
	var empty = (); 
	var tuple = (1,); 
}
```