# Operator ?:

### c?a:b
Evaluates to a if c is true or to b else.

### a?:b
Evaluates to a if a is true or to b else.


## Syntax
```js
/*condition*/ ? /*a*/ : /*b*/
```
or
```js
/*a*/ ?: /*b*/
```

## Examples
### 1)
```js
function main() {
	std::println(true ? 1 : 2);
	std::println(false ? 1 : 2);
}
```
Output:
```
1
2
```

### 2)
```js
function main() {
	std::println(true ?: 42);
	std::println(false ?: 42);
}
```
Output:
```
true
42
```