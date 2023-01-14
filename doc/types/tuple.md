# Tuple 

Tuples are fixed sized collections of values with different types. 
A tuple can be created by a comma separated list inside parenthesis.

**Example**
```js
function main() {
	var tuple = (1, 2.4, 3); // tuple of type tuple<int, float, int>
	std::println(tuple[0]); // 0
	std::println(tuple[1]); // 2.4
	std::println(tuple[2]); // 3
}
```