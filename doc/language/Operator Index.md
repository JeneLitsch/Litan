# Operator []

The index operator is used to access a element in a collection.

## Syntax
```js
/*collection*/[/*key or index*/]
```

## Example
### 1)
```js
function main() {
	var array = [1, 2, 3];
	std::println(array[0]);
	std::println(array[1]);
	std::println(array[2]);
}
```
Output:
```
1
2
3
```

### 2
```js
function main() {
	var string = "Hello World";
	std::println(string[0]);
	std::println(string[1]);
	std::println(string[2]);
}
```
Output:
```
H
e
l
```

### 3
```js
function main() {
	var map = std::map();
	
	map[0] = "foo";
	map["test"] = "bar";

	std::println(map[0]);
	std::println(map["test"]);
	std::println(map[-1]);
}
```
Output:
```
foo
bar
null
```

## Note
An out of range access to an array or string throw an exception.  
An access with a non-existing map key inserts a entry with value null.  