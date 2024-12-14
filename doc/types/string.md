# String

The string type is used to store an array of characters.

## Member Functions

### -> size(): Int

Return the size of the string in bytes.

### -> is_empty(): Bool

Returns whether the string is empty (size == 0)

## Literals

A new string can be created by using a string literal e.g. `"Hello World"` or `"Test"`.

```js
function main() {
	var a = "Hello";
	var b = "World";

	// print HelloWorld
	std::print(a);
	std::println(b);
}
```


## Escape sequences
`\n` for newline  
`\t` for tab  
`\\` for \  
`\"` for "