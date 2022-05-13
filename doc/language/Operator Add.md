# Operator +

The + operator performs an addition or concatination depending on the operands.

## Numeric + Numeric
Performing + on two numbers adds them together.
Bools and chars are always promoted to at least int.

## String + String
Performing + on two strings creates a new concatenated string.

**Example**
```js
function main() {
	std::println("Hello" + " " + "World");
}
```

## Array + Array
Performing + on two arrays creates a new concatenated array.
```js
function main() {
	std::println([1,2,3] + [4,5,6]);
}
```