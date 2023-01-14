# Tuple 

Tuples are fixed sized collections of values with different types. 
A tuple can be created by a comma separated list inside parenthesis.

## Type notation

- `tuple<Ts...>`

**Example**
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
	var tuple = (1,); 
}
```

## Direct deduction

If an integer literal is directly passed to the index operator (tuple[]), the type of the element at the given position will be deduced at compile time. If the compiler cannot deduce the element type, any is deduced instead. 