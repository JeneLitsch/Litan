# Operator + and +=

The + operator performs an addition or concatination depending on the operands.


## Numeric + Numeric
Performs + on two numbers and adds them together.
Bools and chars are always promoted to at least int.


## String + String
Performs + on two strings creates a new concatenated string.


## Array + Array
Performs + on two arrays creates a new concatenated array.

## Examples
### 1)
```js
function main() {
	std::println(20 + 22);
}
```
Output:
```
42
```

### 2)
```js
function main() {
	std::println("Hello" + " " + "World");
}
```
Output:
```
Hello World
```

### 3)
```js
function main() {
	std::println([1,2,3] + [4,5,6]);
}
```
Output:
```
[1, 2, 3, 4, 5, 6]
```